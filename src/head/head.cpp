#include "head.h"

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "option-utils.h"
#include "string-utils.h"
#include "command.h"

static int readFile(const std::string& filePath, const utils::Command& cmd);

int main(int argc, const char* argv[])
{
    utils::Command command = utils::Command(argc, argv)
        .setName("head")
        .setDescription("Shows the head of the file (first n lines)")
        .setVersion("1.0.0")
        .addArgument(utils::CommandArgument("path")
            .setDescription("Path to target file")
            .setRequired(true)
            .setMultiple(true)
        )
        .addOption(utils::CommandOption("lines")
            .setDescription("How many first lines of a file to show")
            .setShortFlag('n')
            .setArgument("10")
        )
        .addOption(utils::CommandOption("show-name")
            .setDescription("Show the name of the file")
            .setShortFlag('v')
            .addConflict("hide-name")
        )
        .addOption(utils::CommandOption("hide-name")
            .setDescription("Hide the name of the file")
            .setShortFlag('q')
            .addConflict("show-name")
        );
    command.parse();

    std::vector<std::string> filePaths = command.getMultiple("path");
    for (const std::string& path : filePaths)
    {
        if ((command.getFlag("show-name") || filePaths.size() > 1) && !command.getFlag("hide-name"))
            std::cout << "==> " << path << " <==" << "\n";

        if (readFile(path, command) != 0)
            return 1;

        if (filePaths.size() > 1) std::cout << std::endl;
    }

    return 0;
}

static int readFile(const std::string &filePath, const utils::Command& cmd)
{
    std::ifstream file(filePath);

    if (!file.is_open())
    {
        std::cerr << "Error: unable to open file \"" << filePath << "\"" << std::endl;
        return 1;
    }

    std::string buffer;
    int lineNumber = 0;
    int lineLimit = std::stoi(cmd.getValue("lines"));
    while (getline(file, buffer) && lineNumber < lineLimit)
    {
        std::cout << buffer << std::endl;
        lineNumber++;
    }
    
    return 0;
}