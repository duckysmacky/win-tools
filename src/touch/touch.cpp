#include "touch.h"

#include <iostream>
#include <string>
#include <vector>
#include <filesystem>

#include <Windows.h>

#include "array-utils.h"
#include "string-utils.h"
#include "option-utils.h"

static int updateFile(std::string filePath, const Options& options);
static int createFile(std::string filePath, const Options& options);
static std::vector<int> getSlashIndexes(const std::string& filePath);

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
        case 'a':
            options.accessTimeOnly = true;
            options.modifyTimeOnly = false;
            break;
        case 'm':
            options.modifyTimeOnly = true;
            options.accessTimeOnly = false;
            break;
        default:
            std::cerr << "Error: unknown option flag \"" << (char)flag << "\"" << std::endl;
            std::cout << MESSAGE_USAGE << std::endl;
            return -1;
        }
    }

    std::vector<std::string> filePaths;
    for (; argIndex < argc; argIndex++)
        filePaths.push_back(argv[argIndex]);

    if (filePaths.empty())
    {
        std::cerr << "Error: missing 1 argument\n";
        std::cout << MESSAGE_USAGE << std::endl;
        return -1;
    }

    for (std::string filePath : filePaths)
    {
        if (options.accessTimeOnly || options.modifyTimeOnly)
        {
            if (updateFile(filePath, options) != 0)
                return 1;
        }
        else
        {
            if (createFile(filePath, options) != 0)
                return 1;
        }
    }

    return 0;
}

static int updateFile(std::string filePath, const Options& options)
{
    HANDLE hFile = CreateFileA(filePath.c_str(), FILE_WRITE_ATTRIBUTES, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    if (hFile == NULL)
    {
        std::cerr << "Error: unable to access file \"" << filePath << "\" (" << GetLastError() << ")" << std::endl;
        return 1;
    }

    SYSTEMTIME sysTime;
    GetSystemTime(&sysTime);

    FILETIME fileTime;
    if (!SystemTimeToFileTime(&sysTime, &fileTime))
    {
        std::cerr << "Error: unable to converting system time (" << GetLastError() << ")" << std::endl;
        CloseHandle(hFile);
        return 1;
    }

    BOOL result = SetFileTime(hFile, NULL, (options.accessTimeOnly) ? &fileTime : NULL, (options.modifyTimeOnly) ? &fileTime : NULL);
    if (!result)
    {
        std::cerr << "Error: unable to update time data for file \"" << filePath << "\" (" << GetLastError() << ")" << std::endl;
        CloseHandle(hFile);
        return 1;
    }

    CloseHandle(hFile);
    return 0;
}

int createFile(std::string filePath, const Options& options)
{
    std::vector<int> slashIndexes = getSlashIndexes(filePath);

    if (slashIndexes.size() > 0)
    {
        // checking if full path exists, if not creating each dir
        std::string dirPath;
        for (int index : slashIndexes)
        {
            dirPath = filePath.substr(0, index);

            if (!std::filesystem::is_directory(dirPath) || !std::filesystem::exists(dirPath))
            {
                std::filesystem::create_directory(dirPath);
            }
        }
    }

    // create the file itself
    HANDLE hFile = CreateFileA(filePath.c_str(), GENERIC_WRITE, NULL, NULL, CREATE_NEW, FILE_ATTRIBUTE_NORMAL, NULL);
    if (hFile == NULL)
    {
        if (GetLastError() == ERROR_ALREADY_EXISTS)
        {
            std::cerr << "Error: file \"" << filePath << "\" already exists" << std::endl;
        }
        else
        {
            std::cerr << "Error: unable to create a new file \"" << filePath << "\" (" << GetLastError() << ")" << std::endl;
        }
        return 1;
    }

    CloseHandle(hFile);
    return 0;
}

static std::vector<int> getSlashIndexes(const std::string& filePath)
{
    std::vector<int> indexes;
    for (int i = 0; i < filePath.length(); i++)
    {
        if (filePath.at(i) == '/' || filePath.at(i) == '\\') indexes.push_back(i);
    }
    return indexes;
}