#include "./head.h"

#include "utils/general.h"
#include "utils/filesystem.h"
#include "command.h"

#include <iostream>
#include <fstream>
#include <string>
#include <vector>


static int readFile(const std::string& filePath, const cmd::Command& cmd);

int main(int argc, const char* argv[])
{
    cmd::Command cmd = cmd::CommandBuilder(NAME, VERSION)
        .setDescription("Shows the head of the file (first n lines)")
        .addArgument(cmd::Argument("path")
            .setDescription("Path to target file")
            .setRequired(true)
            .setMultiple(true)
        )
        .addOption(cmd::Option("lines")
            .setDescription("How many first lines of a file to show")
            .setShortFlag('n')
            .setArgument("10")
        )
        .addOption(cmd::Option("show-name")
            .setDescription("Show the name of the file")
            .setShortFlag('v')
            .addConflict("hide-name")
        )
        .addOption(cmd::Option("hide-name")
            .setDescription("Hide the name of the file")
            .setShortFlag('q')
            .addConflict("show-name")
        )
        .parse(argc, argv);

    std::vector<std::string> filePaths = cmd.getMultiple("path").value();
    for (const std::string& path : filePaths)
    {
        if ((cmd.getFlag("show-name") || filePaths.size() > 1) && !cmd.getFlag("hide-name"))
            std::cout << "==> " << path << " <==" << "\n";

        if (readFile(path, cmd) != 0)
            return 1;

        if (filePaths.size() > 1) std::cout << std::endl;
    }

    return 0;
}

static int readFile(const std::string &filePath, const cmd::Command& cmd)
{
    std::ifstream file(filePath);

    if (!file.is_open())
    {
        std::cerr << "Error: unable to open file \"" << filePath << "\"" << std::endl;
        return 1;
    }

    std::string buffer;
    int lineNumber = 0;
    int lineLimit = std::stoi(cmd.getValue("lines").value());
    while (getline(file, buffer) && lineNumber < lineLimit)
    {
        std::cout << buffer << std::endl;
        lineNumber++;
    }
    
    return 0;
}