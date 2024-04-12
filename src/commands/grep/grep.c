// TODO - implement all options
// TODO - multiple file support
#include "grep.h"

int main(int argc, const char *argv[])
{
    GrepOpts opts;

    // read options
    int opt;
    while ((opt = getopt(argc, (char * const*) argv, GREP_OPTIONS)) != -1)
    {
        switch (opt)
        {
            case 'h': break; // help
            case 'c': opts.c = true; break; // TODO print line count of the matched pattern
            case 'i': opts.i = true; break; // TODO ignore-case
            case 'l': opts.l = true; break; // TODO display filenames only
            case 'n': opts.n = true; break; // show line numbers
            case 'v': opts.v = true; break; // TODO print all lines which didnt match
            case 'e': opts.e = optarg; break; // TODO regular expression to search
            case 'f': opts.f = optarg; break; // TODO take pattern from file
            case 'w': opts.w = true; break; // TODO match whole word only
            case 'o': opts.o = true; break; // TODO print only matching parts of the lines
            default:
                printf("error: unknown option %c!\n", optopt);
                printf(MSG_USAGE);
                return 1;
        }
    }

    // holds all non-options (pattern and path arguments)
    char *noptc[2];
    int i = 0;
    for(; optind < argc; optind++)
    {
        noptc[i] = (char *) argv[optind];
        i++;
    } 

    // check for all required args
    if (i < 2)
    {
        printf("error: missing %d argument[s]!\n", 2 - i);
        printf(MSG_USAGE);
        return 1;
    }

    char *pattern = noptc[0];
    const char *path = noptc[1];

    if (fopen(path, "r"))
    {
        readFile(path, pattern, opts);
    }
    else if (opendir(path))
    {
        if (stroccr(path, '/') > 0 || stroccr(path, '\\') > 0) // if there are slashes
        {
            readDir(path, pattern, opts);
        }
        else
        {
            char *dpath = malloc(sizeof(strlen(path) + 2) * sizeof(char));
            sprintf(dpath, "%s/", path);
            readDir(dpath, pattern, opts);
            free(dpath);
        }
    }
    else
    {
        printf("error: file doesn't exist!");
        return 1;
    }
    
    return 0;
}

void readFile(const char *path, char *pattern, GrepOpts opts)
{
    FILE *file = fopen(path, "r");
    if (file == NULL)
    {
        printf("error reading file!\n");
        fclose(file);
        return;
    }
    
    char line[256];
    int nline = 1, prth = 0;
    while (fgets(line, 256, file))
    {
        if (opts.i)
        {
            printf("i: %d\n", opts.i);
            strlwr(pattern);
            strlwr(line);
        }

        if (strstr(line, pattern))
        {
            if (!opts.c && !opts.l && !opts.v && !opts.o)
            {
                // print filepath at the top
                if (!prth)
                {
                    prtblue("%s\n", path);
                    prth = true;
                }

                // buff for colored pattern word
                char *cpattern = malloc(
                    strlen(pattern) * sizeof(char) + 
                    (2 * sizeof(COLOR_GREEN) + sizeof(char))
                );

                sprintf(cpattern, "%s%s%s", COLOR_GREEN, pattern, COLOR_RESET);
                strrplc(line, 256, pattern, cpattern);

                // check for -n flag
                if (opts.n) { printf("%d %s", nline, line); printf("n: %d\n", opts.n); }
                else printf("%s", line);

                free(cpattern);
            }

        }
        nline++;
    }
    if (prth) printf("\n");
    fclose(file);
    return;
}

void readDir(const char *path, char *pattern, GrepOpts opts)
{
    struct dirent *dEntry;
    DIR *dir = opendir(path);

    while ((dEntry = readdir(dir)))
    {
        char *ename = malloc((strlen(dEntry -> d_name) + 1) * sizeof(char)); // entry name
        strcpy(ename, dEntry -> d_name);
        ename[strlen(ename)] = '\0';

        // ignore "." and ".." files
        if (!strcmp(ename, ".") || !strcmp(ename, "..")) continue;

        char *fpath = malloc( // holds dir path + entry name
            strlen(path) * sizeof(char) +
            (strlen(ename) + 1) * sizeof(char)
        );
        sprintf(fpath, "%s%s", path, ename);

        if (opendir(fpath))
        {
            strcat(fpath, "/");
            readDir(fpath, pattern, opts);
        }
        else if (fopen(fpath, "r"))   
        {
            readFile(fpath, pattern, opts);
        }
        else
        {
            printf("error reading dir: %s\n", fpath);
            return;
        }
        free(fpath);
        free(ename);
    }
    return;
}