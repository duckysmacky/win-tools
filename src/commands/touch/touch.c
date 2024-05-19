#include "touch.h"

int main(int argc, char const *argv[])
{
    Opts opts = Opts_default;
    char *fpath;
    int i;

    // read options
    int opt;
    while ((opt = getopt(argc, (char * const*) argv, OPTION_FLAGS)) != -1)
    {
        switch (opt)
        {
            // case 'h': break; // TODO - show help
            case 'a': opts.a = true; break;
            case 'm': opts.m = true; break;
            case 'd': opts.d = true; break;
            case 'r': opts.r = true; break;
            case 'c': opts.c = true; break;
            case 't': opts.t = true; break;
            default:
                printf("Error: unknown option \"%c\"!\n", optopt);
                printf("Do \"touch -h\" for help\n");
                printf(MSG_USAGE);
                return 1;
        }
    }

    // holds all non-options
    char *noptc[argc];
    i = 0;
    for(; optind < argc; optind++)
    {
        noptc[i] = (char *) argv[optind];
        i++;
    } 

    // check for all required args
    if (i == 0)
    {
        printf("Error: missing 1 argument!\n");
        printf(MSG_USAGE);
        return 1;
    }

    // for each passed path
    for (i = 0; i < arrlen(noptc); i++)
    {
        fpath = noptc[i];
        if (opts.a | opts.m) updateFile(fpath, &opts);
        else createFile(fpath);

    }

    return 0;
}

void updateFile(char *fpath, Opts *opts)
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

    occr = stroccr(fpath, '/') + stroccr(fpath, '\\');
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
