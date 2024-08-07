#include "ls.h"

char *NAME_EXEPTIONS[] = {
    "Makefile"
};

int main(int argc, char const *argv[])
{
    FLAGS flags = FLAGS_DEFAULT;

    int flag;
    while ((flag = getNextFlag(argc, argv, OPTION_FLAGS)) != -1)
    {
        switch (flag)
        {
            // case 'h': break; // TODO - show help
            case 'l': flags.l = true; break;
            case 'a': flags.a = true; break;
            case 't': flags.t = true; break;
            case 'r': flags.r = true; break;
            case 'i': flags.i = true; break;
            case 'g': flags.g = true; break;
            case 'H': flags.H = true; break;
            case 'd': flags.d = true; break;
            case 's': flags.s = true; break;
            case 'A': flags.A = true; break;
            case 'R': flags.R = true; break;
            default:
                // check if the passed flag is a number
                char charFlag = (char) flag;
                if (isdigit(charFlag))
                {
                    flags.rows = atoi(&charFlag);
                    break;
                }
                else
                {
                    fprintf(stderr, "Error: unknown option \"%c\"!\n", optionFlag);
                    printf(MESSAGE_USAGE);
                    return 1;
                }
        }
    }

    // holds specified dir path, else current
    const char *dirpath = argv[optionIndex] ? argv[optionIndex] : ".";

    if (flags.R)
    {
        printBlue("%s:\n", dirpath);
        listDir(dirpath, &flags);
        readDir(dirpath, &flags);
    }
    else
    {
        listDir(dirpath, &flags);
    }

    return 0;
}

ULONG getFileIndex(char *fpath)
{
    HANDLE hFile;
    FILE_FULL_DIR_INFO fileDirInfo;

    hFile = CreateFileA(fpath, GENERIC_READ, (FILE_SHARE_READ | FILE_SHARE_WRITE), NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    GetFileInformationByHandleEx(hFile, FileFullDirectoryInfo, &fileDirInfo, sizeof(fileDirInfo));

    CloseHandle(hFile);
    return fileDirInfo.FileIndex;  
}

bool isDot(char *str)
{
    if (str[0] == '.')
    {
        if (str[1] == '\0' || (str[1] == '.' && str[2] == '\0')) return true;
        else return false;
    }
    else return false;
}

LONGLONG getDirSize(char *dirpath)
{
    LARGE_INTEGER dirSize;
    WIN32_FIND_DATA findData;
    HANDLE hFind;
    LONGLONG dirSizeQuad;
    char *path, *filename, *dirpathA;

    dirpathA = malloc(sizeof(dirpath) + 2);
    sprintf_s(dirpathA, "%s/*", dirpath);
    printf("dirpathA: %s\n", dirpathA);

    hFind = FindFirstFileExA(dirpathA, FindExInfoBasic, &findData, FindExSearchNameMatch, NULL, FIND_FIRST_EX_LARGE_FETCH);
    if (hFind == INVALID_HANDLE_VALUE)
    {
        printf("error getting the find handle for %s!\n", dirpath);
        return 0;
    }

    do
    {
        LARGE_INTEGER fileSize = { 0 };
        filename = findData.cFileName;

        if (findData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
        {
            path = malloc(sizeof(dirpath) + sizeof(filename) + 1);

            sprintf_s(path, "%s/%s", dirpath, filename);
            
            dirSizeQuad = isDot(filename) ? 0 : getDirSize(path);
            dirSize.QuadPart += dirSizeQuad;
            printf("dir: %s | size: %llu\n", filename, dirSizeQuad);
        }
        else
        {
            fileSize.LowPart = findData.nFileSizeLow;
            fileSize.HighPart = findData.nFileSizeHigh;
            dirSize.QuadPart += fileSize.QuadPart;
            printf("file: %s | size: %llu\n", filename, fileSize.QuadPart);
        }
    } while (FindNextFileA(hFind, &findData) != 0);

    printf("size of %s found: %llu\n", dirpath, dirSize.QuadPart);

    free(path);
    free(dirpathA);
    FindClose(hFind);
    return dirSize.QuadPart;
}


// TODO - fix error 24 (ERROR_BAD_LENGTH) somewhere
char* formatLongFile(char *fpath, char *fname)
{
    FILE_STANDARD_INFO standartInfo;
    FILE_FULL_DIR_INFO directoryInfo;
    SYSTEMTIME sysFileTime;
    FILETIME fileTime;
    HANDLE hFile;
    DWORD attrs;
    LARGE_INTEGER fileSizeInfo;
    LONGLONG fileSize, dirSize;
    bool isDir;
    char *longInfo, *modifyMonth, *modifyTime;

    isDir = opendir(fpath) != NULL;

    // Get a handle to the file
    hFile = CreateFileA(
        fpath,
        GENERIC_READ,
        (FILE_SHARE_READ | FILE_SHARE_WRITE),
        NULL,
        OPEN_EXISTING,
        isDir ? (FILE_ATTRIBUTE_NORMAL | FILE_FLAG_BACKUP_SEMANTICS) : FILE_ATTRIBUTE_NORMAL,
        NULL
    );
    if (hFile == INVALID_HANDLE_VALUE) {
        printf("error getting a handle to file %s!\n", fpath);
        goto cleanup;
    }

    // Get file info
    GetFileInformationByHandleEx(hFile, FileStandardInfo, &standartInfo, sizeof(standartInfo));
    GetFileInformationByHandleEx(hFile, FileFullDirectoryInfo, &directoryInfo, sizeof(directoryInfo));
    attrs = directoryInfo.FileAttributes;

    if (!isDir) {
        GetFileSizeEx(hFile, &fileSizeInfo);
        
        fileSize = fileSizeInfo.QuadPart;
    } else {
        dirSize = getDirSize(fpath);
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
    modifyTime = malloc(5 * sizeof(char));
    time_t currTime = time(NULL);
    struct tm locTime = *localtime(&currTime);
    if (locTime.tm_year  + 1900 == (int) sysFileTime.wYear) // compare years - show time if same year
        sprintf_s(modifyTime, "%.2d:%.2d", sysFileTime.wHour, sysFileTime.wMinute);
    else
        sprintf_s(modifyTime, "%d", sysFileTime.wYear);

    // long output: type permissions links owner group size lastMonth lastDate lastTime name
    longInfo = malloc(256 * sizeof(char));
    sprintf_s(longInfo, "%c%c %c%c%c %2lu %s %s %6llu %s %2d %5s %s\n",
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
        fname
    );

    cleanup:

    free(modifyTime);
    CloseHandle(hFile);
    return longInfo ? longInfo : "";
    free(longInfo);
}

void listDir(const char *path, FLAGS *opts)
{
    char *dEntries[1000]; // holds all entries

    CONSOLE_SCREEN_BUFFER_INFO terminalInfo;
    int i, terminalWidth;
    int rowi; // row index
    int rowc = 1; // row counter
    int maxlen = 0;

    const char *ext; // holds file extention
    char *ename; // file name
    int extpos; // index of the extention
    char *cname; // colored entry name
    char *fpath; // full path to file

    DIRECTORY *dir = openDir(path);
    if (dir == NULL)
    {
        printf("Error opening directory \"%s\"\n", path);
        return;
    }

    ENTRY *dirEntry;
    while ((dirEntry = nextEntry(dir)))
    {
        ename = dirEntry->name;
        ext = strrchr(ename, '.'); 
        extpos = (int) (ext - ename); 

        // ignore . and .. files
        if ((!strcmp(ename, ".") || !strcmp(ename, "..")) && !opts->A) continue;
        // ignore dotfiles
        if (extpos == 0 && !(opts->a || opts->A)) continue;
        // ignore everything except dirs if -d
        if (opts->d && !(ext == NULL && strinarr(NAME_EXEPTIONS, sizeof(NAME_EXEPTIONS), ename))) continue;

        // Checking file types and assigning them the correct color
        cname = malloc(sizeof(ename) + sizeof(char) + 2 * sizeof(COLOR_BLACK));
        if
        (
            // if theres no extention (dir) or if it's "." or ".."
            (ext == NULL && strinarr(NAME_EXEPTIONS, sizeof(NAME_EXEPTIONS), ename)) 
            || (strcmp(ename, ".") == 0 || strcmp(ename, "..") == 0)
        )
        {
            sprintf_s(cname, "%s%s/%s", COLOR_BLUE, ename, COLOR_RESET);
        }
        // if index of the extention is 0 (.files and hidden files)
        else if (extpos == 0)
        {
            sprintf_s(cname, "%s%s%s", COLOR_CYAN, ename, COLOR_RESET);
        }
        // all other files (except hidden)
        else
        {
            sprintf_s(cname, "%s%s%s", COLOR_GREEN, ename, COLOR_RESET);
        }

        if (opts->l)
        {
            fpath = malloc(sizeof(path) + sizeof(ename) + 1);
            sprintf_s(fpath, "%s/%s", path, ename);
            dEntries[rowc - 1] = formatLongFile(fpath, cname);
            free(fpath);
        }
        else dEntries[rowc - 1] = cname;

        rowc++;
        // free(cname); DO NOT FREE CNAME. IT STAYS HERE TILL THE END. FREEDOM IS A LIE. CNAME IS AN ETERNAL SLAVE TO THIS PROGRAM.
    }

    if (!opts->l)
    {
        // Automatically setting rows
        if (opts->rows == 0)
        {
            // Get width of the screen
            GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &terminalInfo);
            terminalWidth = terminalInfo.srWindow.Right - terminalInfo.srWindow.Left + 1;

            // Set rows according to how many longest entries fit in a line
            for (i = 0; i < rowc - 1; i++) maxlen = max(maxlen, strlen(dEntries[i]) - 11);
            opts->rows = terminalWidth / maxlen;
        }
        
        int roww[opts->rows]; // holds row width for each column in a row
        memset(roww, 0, opts->rows * sizeof(int));

        // Set the biggest width for each of columns
        for (i = 0; i < rowc - 1; i++)
        {
            rowi = (i >= opts->rows) ? i - (opts->rows * (i / opts->rows)) : i; // row index in roww
            roww[rowi] = max(roww[rowi], strlen(dEntries[i]));
        }

        // Print entries according to width
        for (i = 0; i < rowc - 1; i++)
        {
            rowi = (i >= opts->rows) ? i - (opts->rows * (i / opts->rows)) : i; // row index in roww
            printf("%-*s   ", roww[rowi], dEntries[i]);
            if ((rowi + 1) % opts->rows == 0) printf("\n");
        }
    }
    else
    {
        // TODO - fix the bug where sometimes it works, but sometimes it doesnt
        // I DONT EVEN KNOW AT THIS POINT 😭😭😭

        // Print entries in long format
        for (i = 0; i < rowc - 1; i++) printf("%s", dEntries[i]);
    }

    // just ignore this amalgamation 💀
    if (opts->R) { if (opts->l) printf("\n"); else printf("\n\n"); }

    free(cname);
    closedir(dir);
    return;
}

void readDir(const char *path, FLAGS *opts)
{
    DIRECTORY *dir = openDir(path);

    char *ename; // entry name
    char *dpath; // full path to dir

    ENTRY *dEntry;
    while ((dEntry = nextEntry(dir)))
    {
        ename = dEntry->name;
        if (!strcmp(ename, ".") || !strcmp(ename, "..")) continue;

        dpath = malloc(sizeof(path) + sizeof(ename) + sizeof(char));
        sprintf_s(dpath, "%s/%s", path, ename);

        // try to open entry item as dir
        if (opendir(dpath))
        {
            printBlue("%s:\n", dpath);
            listDir(dpath, opts);
            readDir(dpath, opts);
        }

        free(dpath);
    }

    closedir(dir);
    return;
}