#include "ls.h"

char *NAME_EXEPTIONS[] = {
    "Makefile"
};

int main(int argc, char const *argv[])
{
    Opts opts = LsOpts_default;

    // read options
    int opt;
    while ((opt = getopt(argc, (char * const*) argv, OPTION_FLAGS)) != -1)
    {
        switch (opt)
        {
            // case 'h': break; // TODO - add help
            case 'l': opts.l = true; break;
            case 'a': opts.a = true; break;
            case 't': opts.t = true; break;
            case 'r': opts.r = true; break;
            case 'i': opts.i = true; break;
            case 'g': opts.g = true; break;
            case 'h': opts.h = true; break;
            case 'd': opts.d = true; break;
            case 's': opts.s = true; break;
            case 'A': opts.A = true; break;
            case 'R': opts.R = true; break;
            default:
                // check if the passed flag is a number
                char copt = (char) opt;
                if (isdigit(copt))
                {
                    opts.rows = atoi(&copt);
                    break;
                }
                else
                {
                    printf("error: unknown option \"%c\"!\n", optopt);
                    printf("do ls --help for help\n");
                    printf(MSG_USAGE);
                    return 1;
                }
        }
    }

    // holds specified dir path, else current
    const char *dirpath = argv[optind] ? argv[optind] : "./";

    if (opts.R)
    {
        prtblue("%s:\n", dirpath);
        listDir(dirpath, &opts);
        readDir(dirpath, &opts);
    }
    else
    {
        listDir(dirpath, &opts);
    }

    return 0;
}

// TODO - fix error 24 (ERROR_BAD_LENGTH) somewhere
char* formatLongFile(char *fpath, char *fname)
{
    char *longInfo, *accessMonth, *accessTime;
    FILE_INFO_BY_HANDLE_CLASS fileInfo;
    DWORD fileAttributes;
    PFILETIME fileTime;
    PSYSTEMTIME sFileTime;
    HANDLE hFile;
    
    // TODO - add support for dirs
    if (opendir(fpath)) return "";

    // Get a handle to the file
    hFile = CreateFileA(fpath, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    if (hFile == NULL) {
        printf("error getting a handle to file %s!\n", fpath);
        goto cleanup;
    }

    // Get file info
    GetFileInformationByHandleEx(hFile, FileBasicInfo, &fileInfo, sizeof(fileInfo));
    fileAttributes = GetFileAttributes(fpath);

    // Time manipulations
    fileTime = malloc(sizeof(fileTime));
    sFileTime = malloc(sizeof(sFileTime));
    GetFileTime(hFile, NULL, NULL, fileTime);
    FileTimeToSystemTime(fileTime, sFileTime); // Convert time to human format
    switch (sFileTime->wMonth) // Convert months
    {
        case 1: accessMonth = "Jan"; break;
        case 2: accessMonth = "Feb"; break;
        case 3: accessMonth = "Mar"; break;
        case 4: accessMonth = "Apr"; break;
        case 5: accessMonth = "May"; break;
        case 6: accessMonth = "Jun"; break;
        case 7: accessMonth = "Jul"; break;
        case 8: accessMonth = "Aug"; break;
        case 9: accessMonth = "Sep"; break;
        case 10: accessMonth = "Oct"; break;
        case 11: accessMonth = "Nov"; break;
        case 12: accessMonth = "Dec"; break;
    }
    accessTime = malloc(5 * sizeof(char));
    time_t currTime = time(NULL);
    struct tm locTime = *localtime(&currTime);
    if (locTime.tm_year  + 1900 == (int) sFileTime->wYear) // compare years - show time if same year
        sprintf(accessTime, "%.2d:%.2d", sFileTime->wHour, sFileTime->wMinute);
    else
        sprintf(accessTime, "%d", sFileTime->wYear);

    // long output: type permissions links owner group size lastMonth lastDate lastTime name
    longInfo = malloc(256 * sizeof(char));
    sprintf(longInfo, "%c--------- %2u %s %s %6lu %s %2d %5s %s\n",
        (fileAttributes & FILE_ATTRIBUTE_DIRECTORY) ? 'd' : '-',
        0, // TODO
        "owner", // TODO
        "group", // TODO
        (fileAttributes & FILE_ATTRIBUTE_DIRECTORY) ? 0 : GetFileSize(hFile, NULL),
        accessMonth,
        sFileTime->wDay,
        accessTime,
        fname
    );

    goto cleanup;

    cleanup:

    free(accessTime);
    free(fileTime);
    free(sFileTime);
    CloseHandle(hFile);
    return longInfo ? longInfo : "";
    free(longInfo);
}

void listDir(const char *path, Opts *opts)
{
    struct dirent *dEntry;
    char *dEntries[1000]; // holds all entries

    CONSOLE_SCREEN_BUFFER_INFO terminalInfo;
    DIR *dir;
    int i, terminalWidth;
    int rowi; // row index
    int rowc = 1; // row counter
    int maxlen = 0;

    const char *ext; // holds file extention
    char *ename; // file name
    int extpos; // index of the extention
    char *cname; // colored entry name
    char *fpath; // full path to file

    dir = opendir(path);
    while ((dEntry = readdir(dir)))
    {
        ename = dEntry->d_name;
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
            (ext == NULL && strinarr(NAME_EXEPTIONS, sizeof(NAME_EXEPTIONS), ename)) 
            || (strcmp(ename, ".") == 0 || strcmp(ename, "..") == 0)
        )
        {
            // if theres no extention (dir) or if it's "." or ".."
            sprintf(cname, "%s%s/%s", COLOR_BLUE, ename, COLOR_RESET);
        }
        else if (extpos == 0)
        {
            // if index of the extention is 0 (.files and hidden files)
            sprintf(cname, "%s%s%s", COLOR_CYAN, ename, COLOR_RESET);
        }
        else
        {
            // all other files (except hidden)
            sprintf(cname, "%s%s%s", COLOR_GREEN, ename, COLOR_RESET);
        }

        if (opts->l)
        {
            fpath = malloc(sizeof(path) + sizeof(char) + sizeof(ename));
            sprintf(fpath, "%s/%s", path, ename);
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

void readDir(const char *path, Opts *opts)
{
    struct dirent *dEntry;
    DIR *dir = opendir(path);

    char *ename; // entry name
    char *dpath; // full path to dir

    while ((dEntry = readdir(dir)))
    {
        ename = dEntry->d_name;
        if (!strcmp(ename, ".") || !strcmp(ename, "..")) continue;

        dpath = malloc(sizeof(path) + sizeof(ename) + sizeof(char));
        sprintf(dpath, "%s/%s", path, ename);

        // try to open entry item as dir
        if (opendir(dpath))
        {
            prtblue("%s:\n", dpath);
            listDir(dpath, opts);
            readDir(dpath, opts);
        }

        free(dpath);
    }

    closedir(dir);
    return;
}