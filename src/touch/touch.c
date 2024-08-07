#include "touch.h"

int main(int argc, char const *argv[])
{
    FLAGS flags = FLAGS_DEFAULT;

    int flag;
    while ((flag = getNextFlag(argc, argv, OPTION_FLAGS)) != -1)
    {
        switch (flag)
        {
            // case 'h': break; // TODO - show help
            case 'a': flags.a = true; break;
            case 'm': flags.m = true; break;
            case 'd': flags.d = true; break;
            case 'r': flags.r = true; break;
            case 'c': flags.c = true; break;
            case 't': flags.t = true; break;
            default:
                fprintf(stderr, "Error: unknown option \"%c\"\n", optionFlag);
                printf(MESSAGE_USAGE);
                return 1;
        }
    }

    char *args[64];
    int argCount = 0;
    for(; optionIndex < argc; optionIndex++)
    {
        args[argCount] = (char *) argv[optionIndex];
        argCount++;
    } 

    // check for all required args
    if (argCount == 0)
    {
        fprintf(stderr, "Error: missing 1 argument\n");
        printf(MESSAGE_USAGE);
        return -1;
    }

    // for each passed path
    char* fpath;
    for (argCount = 0; argCount < arrlen(args); argCount++)
    {
        fpath = args[argCount];
        if (flags.a | flags.m) updateFile(fpath, &flags);
        else createFile(fpath);

    }

    return 0;
}

void updateFile(char *fpath, FLAGS *opts)
{
    HANDLE hFile;
    FILETIME fileTime;
    SYSTEMTIME sysTime;

    hFile = CreateFileA(fpath, FILE_WRITE_ATTRIBUTES, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    if (hFile == NULL) { printf("Error has occured while trying to access file: %ld\n", GetLastError()); return; }

    GetSystemTime(&sysTime);
    SystemTimeToFileTime(&sysTime, &fileTime);
    SetFileTime
    (
        hFile,
        NULL,
        (opts->a) ? &fileTime : NULL,
        (opts->m) ? &fileTime : NULL
    );
}

void createFile(char *fpath)
{
    FILE *file;
    char *dirpath;
    int occr, idx, i, j;

    occr = countCharOccurences(fpath, '/') + countCharOccurences(fpath, '\\');
    // holds indexes of slashes
    int idxs[occr];
    
    if (occr > 0)
    {
        // add the index of each slash
        j = 0;
        for (i = 0; i < strlen(fpath); i++)
        {
            if (fpath[i] == '/' || fpath[i] == '\\')
            {
                idxs[j] = i;
                j++;
            }
        }

        // checking if full path exists, if not creating each dir
        for (i = 0; i < arrlen(idxs); i++) // for each index of slash
        {
            idx = idxs[i] + 1; // slash index
            dirpath = malloc(idx + 1);

            strncpy(dirpath, fpath, idx);
            dirpath[idx] = '\0';

            // if dir doesnt exist
            if (opendir(dirpath) == NULL) mkdir(dirpath);

            free(dirpath);
        }
    }

    // create the file itself
    file = fopen(fpath, "w");

    fclose(file);
}
