// TODO - multiple file support
#include "grep.h"

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <filesystem>

#include "colors.h"
#include "array-utils.h"
#include "string-utils.h"
#include "option-utils.h"
#include "fs/Directory.h"

int readFile(std::string filePath, const std::string& pattern, const Options& options);
int readDir(std::string dirPath, const std::string& pattern, const Options& options);

int main(int argc, char* argv[])
{
    Options options;

    // read options
    int flag;
    while ((flag = getNextFlag(argc, argv, OPTION_FLAGS)) != -1)
    {
        switch (flag)
        {
        case 'V':
            std::cout << MESSAGE_VERSION << std::endl;
            return 0;
        case 'h':
            std::cout << MESSAGE_HELP << std::endl;
            return 0;
        case 'i':
            options.ignoreCase = true;
            break;
        case 'n':
            options.showLineNumber = true;
            break;
        case 'c':
            options.onlyCountLines = true;
            options.onlyFileName = false;
            options.onlyUnmatched = false;
            break;
        case 'l':
            options.onlyFileName = true;
            options.onlyCountLines = false;
            options.onlyUnmatched = false;
            break;
        case 'v':
            options.onlyUnmatched = true;
            options.onlyCountLines = false;
            options.onlyFileName = false;
            break;
        case 'R':
            options.recursive = true;
            break;
        case 'f':
            options.patternFilePath = optionArgument;
            break;
        default:
            std::cerr << "Error: unknown option flag \"" << (char)flag << "\"" << std::endl;
            std::cout << MESSAGE_USAGE << std::endl;
            return -1;
        }
    }

    std::string pattern;
    std::vector<std::string> filePaths;
    for (; argIndex < argc; argIndex++)
    {
        if (pattern.empty())
        {
            pattern = argv[argIndex];
            continue;
        }
        filePaths.push_back(argv[argIndex]);
    }

    if (pattern.empty())
    {
        if (options.patternFilePath.empty())
        {
            std::cerr << "Error: missing 2 arguments\n";
            std::cout << MESSAGE_USAGE << std::endl;
            return -1;
        }

        std::ifstream file(options.patternFilePath);
        
        if (!file.is_open())
        {
            std::cerr << "Error: unable to open file \"" << options.patternFilePath << "\"" << std::endl;
            return 1;
        }

        getline(file, pattern);
        file.close();
    }

    if (options.ignoreCase)
        pattern = utils::toLowercase(pattern);

    if (filePaths.empty())
    {
        std::cerr << "Error: missing 1 argument\n";
        std::cout << MESSAGE_USAGE << std::endl;
        return -1;
    }

    for (std::string path : filePaths)
    {
        if (!std::filesystem::exists(path))
        {
            std::cerr << "Error: file \"" << path << "\" doesn\'t exist" << std::endl;
            return 1;
        }

        if (std::filesystem::is_directory(path))
        {
            if (readDir(path, pattern, options) != 0)
                return 1;
        }
        else
        {
            if (readFile(path, pattern, options) != 0)
                return 1;

            if (filePaths.size() > 1)
                std::cout << std::endl;
        }
    }

    return 0;
}

int readFile(std::string filePath, const std::string& pattern, const Options& options)
{
    std::ifstream file(filePath);

    if (!file.is_open())
    {
        std::cerr << "Error: unable to open file \"" << filePath << "\"" << std::endl;
        return 1;
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
        if (options.ignoreCase)
            line = utils::toLowercase(line);

        // 1 != 0 - 1 matched only
        // 1 != 1 - 0 nothing
        // 0 != 1 - 1 not matched only
        // 0 != 0 - 0 nothing
        // if matched or looking for not matched lines only
        while (((foundIndex = line.find(pattern, foundIndex)) != std::string::npos) != options.onlyUnmatched)
        {
            isFound = true;

            if (!options.onlyCountLines && !options.onlyFileName)
            {
                // highlight the found pattern within the line with color
                if (!options.onlyUnmatched)
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

            if (!options.onlyCountLines && !options.onlyFileName)
            {
                if (options.showLineNumber)
                    std::cout << lineNumber << " ";
                std::cout << line << std::endl;
            }
            else if (options.onlyCountLines)
            {
                lineCount++;
            }
        }

        lineNumber++;
    }

    if (options.onlyCountLines)
        std::cout << lineCount << std::endl;

    file.close();
    return 0;
}

int readDir(std::string dirPath, const std::string& pattern, const Options& options)
{
    utils::fs::Directory dir(dirPath);
    std::string entryName;
    std::string filePath;
    for (auto& entry : dir.entries())
    {
        entryName = entry.name;

        // ignore "." and ".." files
        if (entryName == "." || entryName == "..") continue;

        filePath = dirPath + '/' + entryName;

        if (!std::filesystem::exists(filePath))
        {
            std::cerr << "Error: file \"" << filePath << "\" doesn\'t exist" << std::endl;
            return 1;
        }

        if (std::filesystem::is_directory(filePath))
        {
            readDir(filePath, pattern, options);
        }
        else  
        {
            readFile(filePath, pattern, options);
        }
    }

    return 0;
}