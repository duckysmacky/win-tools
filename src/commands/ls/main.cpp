#include "./ls.h"

#include "utils/general.h"
#include "utils/filesystem.h"
#include "utils/logs.h"
#include "utils/colors.h"
#include "command.h"

#include <iostream>
#include <string>
#include <vector>
#include <filesystem>
#include <format>

#include <Windows.h>
#include <time.h>

static void listDir(const std::string& dirPath, const cmd::Command& cmd);
static void readDir(const std::string& dirPath, const cmd::Command& cmd);
static std::string getLongFormat(const std::string& filePath, const std::string& fileName);
static uint32_t getFileIndex(const std::string& filePath);

int main(int argc, const char* argv[])
{
    cmd::Command cmd = cmd::CommandBuilder(NAME, VERSION)
        .setDescription("Lists all the files in the current or the specified directory with a colored output")
        .addArgument(cmd::Argument("path")
            .setDescription("Path to the directory to list files in. Defaults to current directory if not specified")
        )
        .addOption(cmd::Option("long")
            .setDescription(
                "Outputs a more detailed view of the files in the directory, providing last modify times, file type, "
                "file permissions, file size, and other extra information."
            )
            .setShortFlag('l')
        )
        .addOption(cmd::Option("all")
            .setDescription("Show all files in the directory, including hidden, current and parent directories")
            .setShortFlag('a')
            .addConflict("almost-all")
        )
        .addOption(cmd::Option("almost-all")
            .setDescription("Show all files in the directory, including hidden, but not current and parent directories")
            .setShortFlag('A')
            .addConflict("all")
        )
        .addOption(cmd::Option("directories")
            .setDescription("Show only directories, ignore other file types")
            .setShortFlag('d')
            .addConflict("extention")
        )
        .addOption(cmd::Option("recursive")
            .setDescription(
                "Recursively go into every child directory and display files in them. Displays the name of the "
                "currently displayed directory"
            )
            .setShortFlag('R')
        )
        .addOption(cmd::Option("row")
            .setDescription("Output the files in a single vertical row")
            .setShortFlag('1')
            .addConflict("rows")
        )
        .addOption(cmd::Option("rows")
            .setDescription("Speicify the amout of vertical rows to display files in")
            .setShortFlag('n')
            .setArgument("1")
            .addConflict("row")
        )
        /* TODO
        .addOption(cmd::Option("reverse-sort")
            .setDescription("Reverse the sorting order")
            .setShortFlag('r')
        )
        .addOption(cmd::Option("sort-name")
            .setDescription("Sort the order of the files by their name")
            .setShortFlag('N')
        )
        .addOption(cmd::Option("sort-time")
            .setDescription("Sort the order of the files by their last modify time")
            .setShortFlag('t')
        )
        .addOption(cmd::Option("sort-size")
            .setDescription("Sort the order of the files by their size")
            .setShortFlag('s')
        )
        .addOption(cmd::Option("sort-type")
            .setDescription("Sort the order of the files by their type and extention")
            .setShortFlag('T')
        )
        .addOption(cmd::Option("extention")
            .setDescription("Filter the displayed files by their extention")
            .setShortFlag('x')
            .setArgument("exe")
            .addConflict("directories")
        )
        .addOption(cmd::Option("human-size")
            .setDescription("Display the file sizes in a human-readable format (1G, 3KB, 12MB, etc.)")
            .setShortFlag('H')
        )
        */
        .parse(argc, argv);


    std::string dirPath = cmd.getValue("path").has_value() ? cmd.getValue("path").value() : ".";
    if (cmd.getFlag("recursive"))
    {
        colors::cout(colors::ansi::BLUE) << std::format("==> {} <==", dirPath) << colors::endl;
        listDir(dirPath, cmd);
        readDir(dirPath, cmd);
    }
    else
    {
        listDir(dirPath, cmd);
    }

    return 0;
}

static void listDir(const std::string& dirPath, const cmd::Command& cmd)
{
    std::vector<std::string> dirEntries;
    int i, terminalWidth;
    int maxlen = 0;
    size_t extentionPos; // index of the extention
    std::string filePath, fileName, colorName, fileExtention;
    
    fs::Directory dir(dirPath);

    int rowc = 1;
    for (const auto& entry : dir.entries())
    {
        fileName = entry.name;
        extentionPos = fileName.find('.');

        // ignore . and .. files
        if ((fileName == "." || fileName == "..") && !cmd.getFlag("all")) continue;
        // ignore dotfiles
        if (extentionPos == 0 && !(cmd.getFlag("all") || cmd.getFlag("almost-all"))) continue;
        // ignore everything except dirs if -d
        if (cmd.getFlag("directories") && !entry.isDir) continue;

        // Checking file types and assigning them the correct color
        if (extentionPos == std::string::npos || fileName == "." || fileName == "..")
        {
            colorName = colors::paint(COLOR_FILE_DIRECTORY, fileName);
        }
        // if index of the extention is 0 (dot files)
        else if (extentionPos == 0)
        {
            colorName = colors::paint(COLOR_FILE_HIDDEN, fileName);
        }
        // all other files (except hidden)
        else
        {
            colorName = colors::paint(COLOR_FILE_OTHER, fileName);
        }

        dirEntries.push_back(
            cmd.getFlag("long")
            ? getLongFormat(std::format("{}/{}", dirPath, fileName), colorName)
            : colorName
        );

        rowc++;
    }

    if (!cmd.getFlag("long"))
    {
        int rows, rowi;
        
        if (cmd.getFlag("row"))
        {
            rows = 1;
        }
        else if (cmd.getFlag("rows"))
        {
            rows = std::stoi(cmd.getValue("rows").value());
        }
        else // Auto set rows
        {
            // Get width of the screen
            terminalWidth = utils::getTerminalWidth();

            // Set rows according to how many longest entries fit in a line
            for (i = 0; i < rowc - 1; i++) maxlen = (int) max(maxlen, dirEntries[i].size() - MAGIC_WIDTH);
            rows = terminalWidth / maxlen;
        }

        std::vector<int> rowWidths;
        rowWidths.assign(rows, 0);

        // Set the biggest width for each of columns
        for (i = 0; i < rowc - 1; i++)
        {
            rowi = (i >= rows) ? i - (rows * (i / rows)) : i;
            rowWidths[rowi] = (int) max(rowWidths[rowi], dirEntries[i].size());
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
        // Print entries in long format
        for (i = 0; i < rowc - 1; i++) std::cout << dirEntries[i] << std::endl;
    }

    // just ignore this amalgamation 💀
    if (cmd.getFlag("recursive"))
    {
        if (cmd.getFlag("long"))
            std::cout << std::endl;
        else
            std::cout << "\n" << std::endl;
    }
}

static void readDir(const std::string& dirPath, const cmd::Command& cmd)
{
    fs::Directory dir(dirPath);

    for (const auto& entry : dir.entries())
    {
        std::string entryName = entry.name;
        if (entryName == "." || entryName == "..") continue;

        std::string newDirPath = std::format("{}/{}", dirPath, entryName);

        // try to open entry item as dir
        if (std::filesystem::is_directory(newDirPath))
        {
            colors::cout(colors::ansi::BLUE) << std::format("==> {} <==", newDirPath) << colors::endl;
            listDir(newDirPath, cmd);
            readDir(newDirPath, cmd);
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
        logs::logError(std::format("Unable to get access to \"{}\"", fileName), GetLastError());
        CloseHandle(hFile);
        std::exit(1);
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
        fs::Directory dir(filePath);
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
    longInfo = std::format("{}{} {}{}{} {:2} {:11} {} {:2} {:5} {}",
        isDir ? 'd' : '-',
        (attrs & FILE_ATTRIBUTE_HIDDEN) ? 'h' : '-',
        'r',
        (attrs & FILE_ATTRIBUTE_READONLY) ? '-' : 'w',
        '-',
        standartInfo.NumberOfLinks,
        isDir ? dirSize : fileSize,
        modifyMonth,
        sysFileTime.wDay,
        modifyTime,
        fileName
    );

    CloseHandle(hFile);
    return longInfo;
}

static uint32_t getFileIndex(const std::string& filePath)
{
    HANDLE hFile;
    FILE_FULL_DIR_INFO fileDirInfo{};

    hFile = CreateFileA(filePath.c_str(), GENERIC_READ, (FILE_SHARE_READ | FILE_SHARE_WRITE), NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    if (hFile == INVALID_HANDLE_VALUE)
    {
        logs::logError(std::format("Unable to access \"{}\"", filePath), GetLastError());
        std::exit(1);
    }
    GetFileInformationByHandleEx(hFile, FileFullDirectoryInfo, &fileDirInfo, sizeof(fileDirInfo));

    CloseHandle(hFile);
    return fileDirInfo.FileIndex;
}
