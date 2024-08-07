// TODO - multiple file support
#include "grep.h"

int main(int argc, const char *argv[])
{
    FLAGS flags = FLAGS_DEFAULT;

    // read options
    int flag;
    while ((flag = getNextFlag(argc, argv, OPTION_FLAGS)) != -1)
    {
        switch (flag)
        {
            // case '?': break; // TODO - show help
            case 'c': flags.c = true; break;
            case 'i': flags.i = true; break;
            case 'l': flags.l = true; break;
            case 'n': flags.n = true; break;
            case 'v': flags.v = true; break;
            case 'w': flags.w = true; break;
            case 'o': flags.o = true; break;
            case 'e': flags.e = optionArgument; break;
            case 'f': flags.f = optionArgument; break;
            default:
                fprintf(stderr, "Error: unknown option \"%c\"\n", optionFlag);
                printf(MESSAGE_USAGE);
                return -1;
        }
    }

    // holds all arguments (pattern and path arguments)
    char *args[2];
    int argCount = 0;
    for(; optionIndex < argc; optionIndex++)
    {
        args[argCount] = (char *) argv[optionIndex];
        argCount++;
    } 

    // check for all required args
    if (argCount == 0)
    {
        fprintf(stderr, "Error: missing 2 arguments\n");
        printf(MESSAGE_USAGE);
        return -1;
    }
    if (argCount == 1 && !flags.f)
    {
        fprintf(stderr, "Error: missing 1 argument\n");
        printf(MESSAGE_USAGE);
        return -1;
    }

    char *pattern = malloc(1024 * sizeof(char));
    const char *path;
    if (flags.f)
    {
        FILE *patfile = fopen(flags.f, "r");
        if (patfile == NULL)
        {
            fprintf(stderr, "Error: unable to open \"%s\"", flags.f);
            fclose(patfile);
            return -1;
        }
        fgets(pattern, 1024, patfile);
        pattern[strcspn(pattern, "\n")] = 0; // removes newline
        fclose(patfile);

        path = args[0];
    } 
    else 
    {
        pattern = args[0];
        path = args[1];
    }


    if (fopen(path, "r"))
    {
        readFile(path, pattern, &flags);
    }
    else if (openDir(path) != NULL)
    {
        if (countCharOccurences(path, '/') > 0 || countCharOccurences(path, '\\') > 0) // if there are slashes
        {
            readDir(path, pattern, &flags);
        }
        else
        {
            char *dpath = malloc(sizeof(strlen(path) + 2) * sizeof(char));
            sprintf(dpath, "%s/", path);
            readDir(dpath, pattern, &flags);
            free(dpath);
        }
    }
    else
    {
        fprintf(stderr, "Error: unable to open file \"%s\"", path);
        return -1;
    }
    
    free(pattern);
    return 0;
}

void readFile(const char *path, char *pattern, FLAGS *opts)
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
            stringToLower(lpattern, pattern);
            stringToLower(lline, line);
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
                printBlue("%s\n", path);
                prth = true;
            }

            if (!opts->l && !opts->c && !opts->o) // only multi-flag actions
            {
                if (!opts->v) // if not for unmatched, as there wouldn't be any found pattern
                {
                    // check for ignore case color highlight
                    if (opts->i) stringToLower(pattern, pattern);

                    // buff for colored pattern word
                    char *cpattern = malloc(
                        strlen(pattern) * sizeof(char) + 
                        (2 * sizeof(COLOR_GREEN) + sizeof(char))
                    );
                    
                    sprintf(cpattern, "%s%s%s", COLOR_GREEN, pattern, COLOR_RESET);
                    replaceString(line, 256, pattern, cpattern);

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

void readDir(const char *path, char *pattern, FLAGS *opts)
{
    ENTRY *dEntry;
    DIRECTORY *dir = openDir(path);

    while (dEntry = nextEntry(dir))
    {
        char *ename = malloc(sizeof(dEntry->name)); // entry name
        strcpy(ename, dEntry->name);

        // ignore "." and ".." files
        if (!strcmp(ename, ".") || !strcmp(ename, "..")) continue;

        char *fpath = malloc( // holds dir path + entry name
            strlen(path) * sizeof(char) +
            (strlen(ename) + 1) * sizeof(char)
        );
        sprintf(fpath, "%s%s", path, ename);

        if (openDir(fpath) != NULL)
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