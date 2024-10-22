#include "head.h"

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "option-utils.h"
#include "string-utils.h"

using namespace std;

int readFile(const string& filePath, const Options& options);

int main(int argc, char *argv[])
{
    Options options;

    int flag;
    while ((flag = getNextFlag(argc, argv, OPTIONS_FLAGS)) != -1)
    {
        switch (flag)
        {
        case 'h':
            cout << MESSAGE_HELP << endl;
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
                options.nLines = stoi(optionArgument);
                options.nBytes = 0;
                break;
            }
            else
            {
                cerr << "Error: supplied option argument \"" << optionArgument << "\" is not a number value\n";
                cout << MESSAGE_HELP << endl;
                return -1;
            }
        case 'b':
            if (utils::isNumber(optionArgument))
            {
                options.nBytes = stoi(optionArgument);
                options.nLines = 0;
                break;
            }
            else
            {
                cerr << "Error: supplied option argument \"" << optionArgument << "\" is not a number value\n";
                cout << MESSAGE_HELP << endl;
                return -1;
            }
        default:
            cerr << "Error: unknown option flag \"" << (char)flag << "\"\n";
            cout << MESSAGE_USAGE << endl;
            return -1;
        }
    }

    // Holds all non-option arguments (file paths)
    vector<string> filePaths;
    for (; argIndex < argc; argIndex++)
        filePaths.push_back(argv[argIndex]);

    if (filePaths.empty())
    {
        cerr << "Error: missing 1 argument\n";
        cout << MESSAGE_USAGE << endl;
        return -1;
    }

    if (filePaths.size() > 1 && !options.hideFileName)
    {
        options.showFileName = true;
        options.hideFileName = false;
    }

    for (string path : filePaths)
    {
        if (options.showFileName && !options.hideFileName)
            cout << "==> " << path << " <==" << "\n";
        if (readFile(path, options) != 0) return 1;
    }

    return 0;
}

int readFile(const string &filePath, const Options &options)
{
    ifstream file(filePath);

    if (!file.is_open())
    {
        cerr << "Error: unable to open file \"" << filePath << "\"" << endl;
        return 1;
    }

    string buffer;
    int lineNumber = 0;
    while (getline(file, buffer) && lineNumber < options.nLines)
    {
        cout << buffer << endl;
        lineNumber++;
    }
    
    return 0;
}