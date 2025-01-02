#include "touch.h"

#include <iostream>
#include <string>
#include <vector>
#include <filesystem>

#include <Windows.h>

#include "utils.h"
#include "cmd.h"

static void updateFile(const std::string& filePath, const cmd::Command& cmd);
static void createFile(const std::string& filePath, const cmd::Command& cmd);
static std::vector<int> getSlashIndexes(const std::string& filePath);

int main(int argc, const char* argv[])
{
    cmd::Command cmd = cmd::CommandBuilder(NAME, VERSION)
        .setDescription(
            "Creates a new file at the provided location and with the provided name. If the file already "
            "exists, updates the modify and access time values"
        )
        .addArgument(cmd::Argument("path")
            .setDescription("Path and the name of the file to create or update")
            .setRequired(true)
            .setMultiple(true)
        )
        .addOption(cmd::Option("access-time")
            .setDescription("Only set the access time of the existing file to the current")
            .setShortFlag('a')
            .addConflict("modify-time")
        )
        .addOption(cmd::Option("modify-time")
            .setDescription("Only set the modify time of the existing file to the current")
            .setShortFlag('m')
            .addConflict("access-time")
        )
        // TODO
        // .addOption(cmd::Option("from-string")
        //     .setDescription("Use the specified YYMMDDhhmm timestamp to update time on the existing file")
        //     .setShortFlag('s')
        //     .setArgument("----------")
        // )
        .parse(argc, argv);

    std::vector<std::string> filePaths = cmd.getMultiple("path").value();
    for (const std::string& filePath : filePaths)
    {
        if (std::filesystem::exists(filePath))
        {
            updateFile(filePath, cmd);
        }
        else
        {
            createFile(filePath, cmd);
        }
    }

    return 0;
}

static void updateFile(const std::string& filePath, const cmd::Command& cmd)
{
    HANDLE hFile = CreateFileA(filePath.c_str(), FILE_WRITE_ATTRIBUTES, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    if (hFile == INVALID_HANDLE_VALUE)
    {
        utils::logError(std::format("Unable to access \"{}\"", filePath), GetLastError());
        CloseHandle(hFile);
        std::exit(1);
    }

    SYSTEMTIME sysTime;
    GetSystemTime(&sysTime);

    FILETIME fileTime;
    BOOL success = SystemTimeToFileTime(&sysTime, &fileTime);
    if (!success)
    {
        utils::logError("Unable to convert system time", GetLastError());
        CloseHandle(hFile);
        std::exit(1);
    }

    success = SetFileTime(
        hFile, NULL,
        !cmd.getFlag("modify-time") ? &fileTime : NULL,
        !cmd.getFlag("access-time") ? &fileTime : NULL
    );
    if (!success)
    {
        utils::logError(std::format("Unable to update time data for \"{}\"", filePath), GetLastError());
        CloseHandle(hFile);
        std::exit(1);
    }

    CloseHandle(hFile);
}

static void createFile(const std::string& filePath, const cmd::Command& cmd)
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
    if (hFile == INVALID_HANDLE_VALUE)
    {
        utils::logError(std::format("Unable to create \"{}\"", filePath), GetLastError());
        CloseHandle(hFile);
        std::exit(1);
    }

    CloseHandle(hFile);
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