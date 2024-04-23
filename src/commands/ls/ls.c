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
                printf("error: unknown option %c!\n", optopt);
                printf("do %s --help for help\n", argv[0]);
                printf(MSG_USAGE);
                return 1;
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

void listDir(const char *path, Opts *opts)
{
    struct dirent *dEntry;
    DIR *dir = opendir(path);

    while ((dEntry = readdir(dir)))
    {
        char *name = malloc((strlen(dEntry -> d_name) + 1) * sizeof(char)); // file name
        strcpy(name, dEntry -> d_name);
        // ignore . and .. files
        if ((!strcmp(name, ".") || !strcmp(name, "..")) && !opts->A) {
            continue;
        }

        const char *ext = strrchr(name, '.'); // holds file extention
        if (ext == NULL && strinarr(NAME_EXEPTIONS, sizeof(NAME_EXEPTIONS), name)) // if theres no extention (dir)
        { 
            prtblue("%s/ ", name);
        }
        else if (((int)(ext - name)) == 0) // if index of the extention is 0 (.files and hidden files)
        { 
            prtcyan("%s ", name);
        }
        else // all other files
        { 
            prtgreen("%s ", name);
        }

        free(name);
    }

    puts("\n");
    closedir(dir);
    return;
}

void readDir(const char *path, Opts *opts)
{
    struct dirent *dEntry;
    DIR *dir = opendir(path);

    while ((dEntry = readdir(dir)))
    {
        char *ename = dEntry->d_name; // entry name
        if (!strcmp(ename, ".") || !strcmp(ename, "..")) continue;

        char *dpath = malloc(sizeof(path) + sizeof(ename) + sizeof(char) * 2); // full path to dir
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