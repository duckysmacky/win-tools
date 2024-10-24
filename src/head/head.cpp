#include "head.h"

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "option-utils.h"
#include "string-utils.h"

int readFile(const std::string& filePath, const Options& options);

int main(int argc, char* argv[])
{
    Options options;

    int flag;
    while ((flag = getNextFlag(argc, argv, OPTIONS_FLAGS)) != -1)
    {
        switch (flag)
        {
        case 'V':
            std::cout << MESSAGE_VERSION << std::endl;
            return 0;
        case 'h':
            std::cout << MESSAGE_HELP << std::endl;
            return 0;
        case 'v':
            options.showFileName = true;
            options.hideFileName = false;
            break;
        case 'q':
            options.hideFileName = true;
            options.showFileName = false;
            break;
        case 'n': 
            if (utils::isNumber(optionArgument))
            {
                options.nLines = std::stoi(optionArgument);
                break;
            }
            else
            {
                std::cerr << "Error: supplied option argument \"" << optionArgument << "\" is not a number value" << std::endl;
                std::cout << MESSAGE_HELP << std::endl;
                return -1;
            }
        default:
            std::cerr << "Error: unknown option flag \"" << (char)flag << "\"" << std::endl;
            std::cout << MESSAGE_USAGE << std::endl;
            return -1;
        }
    }

    // Holds all non-option arguments (file paths)
    std::vector<std::string> filePaths;
    for (; argIndex < argc; argIndex++)
        filePaths.push_back(argv[argIndex]);

    if (filePaths.empty())
    {
        std::cerr << "Error: missing 1 argument\n";
        std::cout << MESSAGE_USAGE << std::endl;
        return -1;
    }

    if (filePaths.size() > 1 && !options.hideFileName)
    {
        options.showFileName = true;
        options.hideFileName = false;
    }

    for (std::string path : filePaths)
    {
        if (options.showFileName && !options.hideFileName)
            std::cout << "==> " << path << " <==" << "\n";

        if (readFile(path, options) != 0)
            return 1;

        if (filePaths.size() > 1) std::cout << std::endl;
    }

    return 0;
}

int readFile(const std::string &filePath, const Options &options)
{
    std::ifstream file(filePath);

    if (!file.is_open())
    {
        std::cerr << "Error: unable to open file \"" << filePath << "\"" << std::endl;
        return 1;
    }

    std::string buffer;
    int lineNumber = 0;
    while (getline(file, buffer) && lineNumber < options.nLines)
    {
        std::cout << buffer << std::endl;
        lineNumber++;
    }
    
    return 0;
}