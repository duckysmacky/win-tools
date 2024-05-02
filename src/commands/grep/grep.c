// TODO - multiple file support
#include "grep.h"

int main(int argc, const char *argv[])
{
    Opts opts = Opts_default;

    // read options
    int opt;
    while ((opt = getopt(argc, (char * const*) argv, OPTION_FLAGS)) != -1)
    {
        switch (opt)
        {
            // case '?': break; // TODO - show help
            case 'c': opts.c = true; break;
            case 'i': opts.i = true; break;
            case 'l': opts.l = true; break;
            case 'n': opts.n = true; break;
            case 'v': opts.v = true; break;
            case 'w': opts.w = true; break;
            case 'o': opts.o = true; break;
            case 'e': opts.e = optarg; break;
            case 'f': opts.f = optarg; break;
            default:
                printf("error: unknown option %c!\n", optopt);
                printf("do %s --help for help\n", argv[0]);
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
    if (i == 0)
    {
        printf("error: missing 2 arguments!\n");
        printf(MSG_USAGE);
        return 1;
    }
    if (i == 1 && !opts.f)
    {
        printf("error: missing 1 argument!\n");
        printf(MSG_USAGE);
        return 1;
    }

    char *pattern = malloc(1024 * sizeof(char));
    const char *path;
    if (opts.f)
    {
        FILE *patfile = fopen(opts.f, "r");
        if (patfile == NULL)
        {
            printf("error: file %s doesn't exist!", opts.f);
            fclose(patfile);
            return 1;
        }
        fgets(pattern, 1024, patfile);
        pattern[strcspn(pattern, "\n")] = 0; // removes newline
        fclose(patfile);

        path = noptc[0];
    } 
    else 
    {
        pattern = noptc[0];
        path = noptc[1];
    }


    if (fopen(path, "r"))
    {
        readFile(path, pattern, &opts);
    }
    else if (opendir(path))
    {
        if (stroccr(path, '/') > 0 || stroccr(path, '\\') > 0) // if there are slashes
        {
            readDir(path, pattern, &opts);
        }
        else
        {
            char *dpath = malloc(sizeof(strlen(path) + 2) * sizeof(char));
            sprintf(dpath, "%s/", path);
            readDir(dpath, pattern, &opts);
            free(dpath);
        }
    }
    else
    {
        printf("error: file %s doesn't exist!", path);
        return 1;
    }
    
    free(pattern);
    return 0;
}

void readFile(const char *path, char *pattern, Opts *opts)
{
    FILE *file = fopen(path, "r");
    if (file == NULL)
    {
        printf("error reading file!");
        fclose(file);
        return;
    }
    
    char line[256];
    char *fpat; // holds found pattern
    int nline = 1, linec = 0;
    int prth = false; // printed filepath status
    while (fgets(line, 256, file))
    {
        if (opts->i)
        {
            char *lpattern = malloc(strlen(pattern) * sizeof(char));
            char *lline = malloc(strlen(line) * sizeof(char));
            strtolwr(lpattern, pattern);
            strtolwr(lline, line);
            fpat = strstr(lline, lpattern);
            free(lline);
            free(lpattern);
        }
        else fpat = strstr(line, pattern);

        // f    v
        // 1 != 0 - 1 found only
        // 1 != 1 - 0 nothing
        // 0 != 1 - 1 not found only
        // 0 != 0 - 0 nothing
        if ((fpat != NULL) != opts->v) // if matched or looking for unmatched lines only
        {
            // print filepath at the top if haven't yet
            if (!prth)
            {
                prtblue("%s\n", path);
                prth = true;
            }

            if (!opts->l && !opts->c && !opts->o) // only multi-flag actions
            {
                if (!opts->v) // if not for unmatched, as there wouldn't be any found pattern
                {
                    // check for ignore case color highlight
                    if (opts->i) strtolwr(pattern, pattern);

                    // buff for colored pattern word
                    char *cpattern = malloc(
                        strlen(pattern) * sizeof(char) + 
                        (2 * sizeof(COLOR_GREEN) + sizeof(char))
                    );
                    
                    sprintf(cpattern, "%s%s%s", COLOR_GREEN, pattern, COLOR_RESET);
                    strrplc(line, 256, pattern, cpattern);

                    free(cpattern);
                }

                // check for -n flag
                if (opts->n) printf("%d %s", nline, line);
                else printf("%s", line);
            }
            else if (opts->c) // only count lines
            {
                linec++;
            }
        }
        nline++;
    }
    if (opts->c) printf("%d", linec);
    // if (prth) printf("\n");
    free(fpat);
    fclose(file);
    return;
}

void readDir(const char *path, char *pattern, Opts *opts)
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

    closedir(dir);
    return;
}