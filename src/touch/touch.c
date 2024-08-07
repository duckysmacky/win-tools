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
    char* filePath;
    for (argCount = 0; argCount < arrlen(args); argCount++)
    {
        filePath = args[argCount];
        if (flags.a | flags.m)
        {
            if (updateFile(filePath, &flags) == -1) return -1;
        }
        else
        {
            if (createFile(filePath) == -1) return -1;
        }
    }

    return 0;
}

int updateFile(char *filePath, FLAGS *opts)
{
    HANDLE hFile = CreateFileA(filePath, FILE_WRITE_ATTRIBUTES, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    if (hFile == NULL)
    {
        fprintf(stderr, "Error: unable to access the file at \"%s\" (%ld)\n", filePath, GetLastError());
        CloseHandle(hFile);
        return -1;
    }

    SYSTEMTIME sysTime;
    GetSystemTime(&sysTime);

    FILETIME fileTime;
    if (!SystemTimeToFileTime(&sysTime, &fileTime))
    {
        fprintf(stderr, "Error: unable to converting system time (%ld)\n", GetLastError());
        CloseHandle(hFile);
        return -1;
    }

    if (!SetFileTime(
            hFile,
            NULL,
            (opts->a) ? &fileTime : NULL,
            (opts->m) ? &fileTime : NULL
        )
    ) {
        fprintf(stderr, "Error: unable to update file time for \"%s\" (%ld)\n", filePath, GetLastError());
        CloseHandle(hFile);
        return -1;
    }

    CloseHandle(hFile);
    return 0;
}

int createFile(char *filePath)
{
    int slashOccurences = countCharOccurences(filePath, '/') + countCharOccurences(filePath, '\\');
    int *slashIndexes = malloc(sizeof(int) * slashOccurences);
    
    if (slashOccurences > 0)
    {
        // add the index of each slash
        int j = 0;
        int i;
        for (i = 0; i < strlen(filePath); i++)
        {
            if (filePath[i] == '/' || filePath[i] == '\\')
            {
                slashIndexes[j] = i;
                j++;
            }
        }

        // checking if full path exists, if not creating each dir
        int slashIndex;
        char* directoryPath;
        for (i = 0; i < arrlen(slashIndexes); i++) // for each index of slash
        {
            slashIndex = slashIndexes[i] + 1;
            directoryPath = malloc(slashIndex);

            strncpy_s(directoryPath, sizeof(directoryPath), filePath, sizeof(filePath));

            // if dir doesnt exist
            if (openDir(directoryPath) == NULL)
            {
                if (!CreateDirectoryW(directoryPath, NULL))
                {
                    fprintf(stderr, "Error: unable to create directory at \"&s\" (%ld)\n", directoryPath, GetLastError());
                    free(directoryPath);
                    return -1;
                }
            }

            free(directoryPath);
        }
    }

    // create the file itself
    HANDLE hFile = CreateFileA(filePath, GENERIC_WRITE, NULL, NULL, CREATE_NEW, FILE_ATTRIBUTE_NORMAL, NULL);
    if (hFile == NULL)
    {
        if (GetLastError() == ERROR_ALREADY_EXISTS)
        {
            fprintf(stderr, "Error: file at \"&s\" already exists!", filePath);
        }
        else
        {
            fprintf(stderr, "Error: unable to create a new file at \"&s\" (%ld)", filePath, GetLastError());
        }
        CloseHandle(hFile);
        return -1;
    }

    CloseHandle(hFile);
    return 0;
}
