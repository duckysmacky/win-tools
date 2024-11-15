#include "ls.h"

#include <iostream>
#include <string>
#include <vector>
#include <filesystem>
#include <format>

#include <Windows.h>
#include <time.h>

#include "colors.h"
#include "array-utils.h"
#include "string-utils.h"
#include "option-utils.h"
#include "fs/Directory.h"

void listDir(const std::string& dirPath, const Options& options);
void readDir(const std::string& dirPath, const Options& options);

uint32_t getFileIndex(const std::string& filePath);

std::string getLongFormat(const std::string& filePath, const std::string& fileName);

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
        case 'l':
            options.longFormat = true;
            break;
        case 'a':
            options.showHidden = true;
            options.showAll = false;
            break;
        case 'A':
            options.showAll = true;
            options.showHidden = false;
            break;
        case 'd':
            options.listDirs = true;
            break;
        case 'R':
            options.recursive = true;
            break;
        default:
            std::string strFlag = (char*)flag;
            if (utils::isNumber(strFlag))
            {
                options.rows = std::stoi(strFlag);
                std::cout << "Set row flag to: " << options.rows << std::endl;
                break;
            }
            else
            {
                std::cerr << "Error: unknown option flag \"" << strFlag << "\"" << std::endl;
                std::cout << MESSAGE_USAGE << std::endl;
                return -1;
            }
        }
    }

    std::string dirPath = argv[argIndex] ? argv[argIndex] : ".";

    if (options.recursive)
    {
        std::cout << dirPath << ":" << std::endl;
        //utils::ccout(colors::BLUE) << dirPath << ":\n";
        listDir(dirPath, options);
        readDir(dirPath, options);
    }
    else
    {
        listDir(dirPath, options);
    }

    return 0;
}

uint32_t getFileIndex(const std::string& filePath)
{
    HANDLE hFile;
    FILE_FULL_DIR_INFO fileDirInfo{};

    hFile = CreateFileA(filePath.c_str(), GENERIC_READ, (FILE_SHARE_READ | FILE_SHARE_WRITE), NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    GetFileInformationByHandleEx(hFile, FileFullDirectoryInfo, &fileDirInfo, sizeof(fileDirInfo));

    CloseHandle(hFile);
    return fileDirInfo.FileIndex;
}

void listDir(const std::string& dirPath, const Options& options)
{
    std::vector<std::string> dirEntries;
    CONSOLE_SCREEN_BUFFER_INFO terminalInfo;
    int i, terminalWidth;
    int maxlen = 0;
    size_t extentionPos; // index of the extention
    std::string filePath, fileName, colorName, fileExtention;

    utils::fs::Directory dir(dirPath);

    int rowc = 1;
    for (auto& entry : dir.entries())
    {
        fileName = entry.name;
        extentionPos = fileName.find('.');

        // ignore . and .. files
        if ((fileName == "." || fileName == "..") && !options.showAll) continue;
        // ignore dotfiles
        if (extentionPos == 0 && !(options.showAll || options.showHidden)) continue;
        // ignore everything except dirs if -d
        if (options.listDirs && !entry.isDir) continue;

        // Checking file types and assigning them the correct color
        if (extentionPos == std::string::npos || fileName == "." || fileName == "..")
        {
            colorName = std::format("{}{}/{}", FILE_COLOR_DIRECTORY, fileName, colors::RESET);
        }
        // if index of the extention is 0 (dot files)
        else if (extentionPos == 0)
        {
            colorName = std::format("{}{}{}", FILE_COLOR_HIDDEN, fileName, colors::RESET);
        }
        // all other files (except hidden)
        else
        {
            colorName = std::format("{}{}{}", FILE_COLOR_OTHER, fileName, colors::RESET);
        }

        dirEntries.push_back(options.longFormat
            ? getLongFormat(std::format("{}/{}", dirPath, fileName), colorName)
            : colorName);

        rowc++;
        // free(cname); DO NOT FREE CNAME. IT STAYS HERE TILL THE END. FREEDOM IS A LIE. CNAME IS AN ETERNAL SLAVE TO THIS PROGRAM.
        // i will just keep this comment because it's funny
    }

    if (!options.longFormat)
    {
        int rows, rowi;
        // Automatically setting rows
        if (options.rows == 0)
        {
            // Get width of the screen
            GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &terminalInfo);
            terminalWidth = terminalInfo.srWindow.Right - terminalInfo.srWindow.Left + 1;

            // Set rows according to how many longest entries fit in a line
            for (i = 0; i < rowc - 1; i++) maxlen = max(maxlen, dirEntries[i].size() - 11);
            rows = terminalWidth / maxlen;
        }
        else
            rows = options.rows;
        
        std::vector<int> rowWidths;
        rowWidths.assign(rows, 0);

        // Set the biggest width for each of columns
        for (i = 0; i < rowc - 1; i++)
        {
            rowi = (i >= rows) ? i - (rows * (i / rows)) : i;
            rowWidths[rowi] = max(rowWidths[rowi], dirEntries[i].size());
        }

        // Print entries according to width
        for (i = 0; i < rowc - 1; i++)
        {
            rowi = (i >= rows) ? i - (rows * (i / rows)) : i;
            printf("%-*s   ", rowWidths[rowi], dirEntries[i].c_str()); // TODO: migrate to std::cout (I have no clue what is written here)
            if ((rowi + 1) % rows == 0) std::cout << std::endl;
        }
    }
    else
    {
        // TODO - fix the bug where sometimes it works, but sometimes it doesnt
        // I DONT EVEN KNOW AT THIS POINT 😭😭😭

        // Print entries in long format
        for (i = 0; i < rowc - 1; i++) std::cout << dirEntries[i] << std::endl;
    }

    // just ignore this amalgamation 💀
    if (options.recursive)
    {
        if (options.longFormat) std::cout << std::endl;
        else std::cout << "\n" << std::endl;
    }

    return;
}

void readDir(const std::string& dirPath, const Options& options)
{
    utils::fs::Directory dir(dirPath);

    for (auto& entry : dir.entries())
    {
        std::string entryName = entry.name;
        if (entryName == "." || entryName == "..") continue;

        std::string newDirPath = std::format("{}/{}", dirPath, entryName);

        // try to open entry item as dir
        if (std::filesystem::is_directory(newDirPath))
        {
            utils::ccout(colors::BLUE) << newDirPath << ":";
            listDir(newDirPath, options);
            readDir(newDirPath, options);
        }
    }
}

// TODO - fix error 24 (ERROR_BAD_LENGTH) somewhere
std::string getLongFormat(const std::string& filePath, const std::string& fileName)
{
    FILE_STANDARD_INFO standartInfo{};
    FILE_FULL_DIR_INFO directoryInfo{};
    SYSTEMTIME sysFileTime;
    FILETIME fileTime;
    HANDLE hFile;
    DWORD attrs;
    LARGE_INTEGER fileSizeInfo;
    LONGLONG fileSize, dirSize;
    bool isDir;
    std::string modifyMonth, modifyTime, longInfo;

    isDir = std::filesystem::is_directory(filePath);

    // Get a handle to the file
    hFile = CreateFileA(
        filePath.c_str(),
        GENERIC_READ,
        (FILE_SHARE_READ | FILE_SHARE_WRITE),
        NULL,
        OPEN_EXISTING,
        isDir ? (FILE_ATTRIBUTE_NORMAL | FILE_FLAG_BACKUP_SEMANTICS) : FILE_ATTRIBUTE_NORMAL,
        NULL
    );

    if (hFile == INVALID_HANDLE_VALUE)
    {
        std::cout << "Error getting a handle to \"" << filePath << "\"!" << std::endl;
        CloseHandle(hFile);
        return "";
    }

    // Get file info
    GetFileInformationByHandleEx(hFile, FileStandardInfo, &standartInfo, sizeof(standartInfo));
    GetFileInformationByHandleEx(hFile, FileFullDirectoryInfo, &directoryInfo, sizeof(directoryInfo));
    attrs = directoryInfo.FileAttributes;

    if (!isDir)
    {
        GetFileSizeEx(hFile, &fileSizeInfo);
        fileSize = fileSizeInfo.QuadPart;
    }
    else
    {
        utils::fs::Directory dir(filePath);
        dirSize = dir.size();
    }

    // Time manipulations
    GetFileTime(hFile, NULL, NULL, &fileTime);
    FileTimeToSystemTime(&fileTime, &sysFileTime); // Convert time to human format
    switch (sysFileTime.wMonth) // Convert months
    {
        case 1: modifyMonth = "Jan"; break;
        case 2: modifyMonth = "Feb"; break;
        case 3: modifyMonth = "Mar"; break;
        case 4: modifyMonth = "Apr"; break;
        case 5: modifyMonth = "May"; break;
        case 6: modifyMonth = "Jun"; break;
        case 7: modifyMonth = "Jul"; break;
        case 8: modifyMonth = "Aug"; break;
        case 9: modifyMonth = "Sep"; break;
        case 10: modifyMonth = "Oct"; break;
        case 11: modifyMonth = "Nov"; break;
        case 12: modifyMonth = "Dec"; break;
    }
    time_t currTime = time(NULL);
    struct tm locTime;
    localtime_s(&locTime, &currTime);
    modifyTime = (locTime.tm_year + 1900 == (int)sysFileTime.wYear)  // compare years - show time if same year
        ? std::format("{}:{}", sysFileTime.wHour, sysFileTime.wMinute)
        : std::format("{}", sysFileTime.wYear);

    // long output: type permissions links owner group size lastMonth lastDate lastTime name
    longInfo = std::format("{}{} {}{}{} {:2} {} {} {:10} {} {:2} {:5} {}",
        isDir ? 'd' : '-',
        (attrs & FILE_ATTRIBUTE_HIDDEN) ? 'h' : '-',
        'r',
        (attrs & FILE_ATTRIBUTE_READONLY) ? '-' : 'w',
        '-',
        standartInfo.NumberOfLinks,
        "owner", // TODO - add owner
        "group", // TODO - add group
        isDir ? dirSize : fileSize,
        modifyMonth,
        sysFileTime.wDay,
        modifyTime,
        fileName
    );

    CloseHandle(hFile);
    return longInfo;
}