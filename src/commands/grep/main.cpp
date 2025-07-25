#include "./grep.h"

#include "utils/general.h"
#include "utils/filesystem.h"
#include "utils/logs.h"
#include "command.h"

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <filesystem>

static void readFile(std::string filePath, const std::string& pattern, const cmd::Command& cmd);
static void readDir(std::string dirPath, const std::string& pattern, const cmd::Command& cmd);

int main(int argc, const char* argv[])
{
    cmd::Command cmd = cmd::CommandBuilder(NAME, VERSION)
        .setDescription("Searches a file for matching lines using the provided pattern.")
        .addArgument(cmd::Argument("pattern")
            .setDescription("Pattern to match against")
            .setRequired(true)
        )
        .addArgument(cmd::Argument("file")
            .setDescription("File to search for pattern in")
            .setRequired(true)
            .setMultiple(true)
        )
        .addOption(cmd::Option("ignore-case")
            .setDescription("Ignore case while matching the pattern")
            .setShortFlag('i')
        )
        .addOption(cmd::Option("show-lines")
            .setDescription("Show of number of the line which was matched")
            .setShortFlag('n')
        )
        .addOption(cmd::Option("count-lines")
            .setDescription("Only count matched lines, don\'t output them")
            .setShortFlag('c')
            .addConflict("only-name")
        )
        .addOption(cmd::Option("only-name")
            .setDescription("Output only the name of the matched files")
            .setShortFlag('l')
            .addConflict("count-lines")
        )
        .addOption(cmd::Option("unmatched")
            .setDescription("Output only unmatched lines")
            .setShortFlag('v')
        )
        .addOption(cmd::Option("recursive")
            .setDescription("Recursively traverse directory and match every file")
            .setShortFlag('R')
        )
        .parse(argc, argv);

    std::string pattern = cmd.getFlag("ignore-case")
        ? utils::toLowercase(cmd.getValue("pattern").value())
        : cmd.getValue("pattern").value();

    std::vector<std::string> filePaths = cmd.getMultiple("file").value();
    for (const std::string& path : filePaths)
    {
        if (!std::filesystem::exists(path))
        {
            logs::logError(std::format("File \"{}\" doesn't exist", path));
            std::exit(1);
        }

        if (std::filesystem::is_directory(path))
        {
            readDir(path, pattern, cmd);
        }
        else
        {
            readFile(path, pattern, cmd);

            if (filePaths.size() > 1)
                std::cout << std::endl;
        }
    }

    return 0;
}

static void readFile(std::string filePath, const std::string& pattern, const cmd::Command& cmd)
{
    std::ifstream file(filePath);

    if (!file.is_open())
    {
        logs::logError(std::format("Unable to opem file \"{}\"", filePath));
        std::exit(1);
    }

    std::string colored;
    size_t foundIndex = 0;
    int lineNumber = 1, lineCount = 0;
    bool isFound = false, isPrinted = false;

    std::string line;
    while (getline(file, line))
    {
        foundIndex = 0;
        isFound = false;
        if (cmd.getFlag("ignore-case"))
            line = utils::toLowercase(line);

        // Only if matched OR looking for not matched
        while ((int)((foundIndex = line.find(pattern, foundIndex)) != std::string::npos) + (int)(cmd.getFlag("unmatched")) == 1)
        {
            isFound = true;

            if (!cmd.getFlag("count-lines") && !cmd.getFlag("only-name"))
            {
                // highlight the found pattern within the line with color
                if (!cmd.getFlag("unmatched"))
                {
                    std::string colored = COLOR_GREEN + pattern + COLOR_RESET;
                    line.replace(foundIndex, pattern.size(), colored);
                    foundIndex += colored.length();
                }
                else
                {
                    break;
                }
            }
            else
            {
                foundIndex += pattern.length();
            }
        }

        if (isFound)
        {
            if (!isPrinted)
            {
                std::cout << "==> " << filePath << " <==" << std::endl;
                isPrinted = true;
            }

            if (!cmd.getFlag("count-lines") && !cmd.getFlag("only-name"))
            {
                if (cmd.getFlag("show-lines"))
                    std::cout << lineNumber << " ";
                std::cout << line << std::endl;
            }
            else if (cmd.getFlag("count-lines"))
            {
                lineCount++;
            }
        }

        lineNumber++;
    }

    if (cmd.getFlag("count-lines"))
        std::cout << lineCount << std::endl;

    file.close();
}

static void readDir(std::string dirPath, const std::string& pattern, const cmd::Command& cmd)
{
    fs::Directory dir(dirPath);
    std::string entryName;
    std::string filePath;
    for (const auto& entry : dir.entries())
    {
        entryName = entry.name;

        // ignore "." and ".." files
        if (entryName == "." || entryName == "..") continue;

        filePath = dirPath + '/' + entryName;

        if (!std::filesystem::exists(filePath))
        {
            logs::logError(std::format("File \"{}\" doesn't exist", filePath));
            std::exit(1);
        }

        if (std::filesystem::is_directory(filePath))
        {
            readDir(filePath, pattern, cmd);
        }
        else  
        {
            readFile(filePath, pattern, cmd);
        }
    }
}