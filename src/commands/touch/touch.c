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
            case 'a': break;
            case 'm': break;
            case 'd': break;
            case 'r': break;
            case 'c': break;
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

        createFile(fpath);
    }

    return 0;
}

void createFile(char *fpath)
{
    FILE *file;
    char *dirpath;
    int toccr, idx, i, j;

    toccr = stroccr(fpath, '/') + stroccr(fpath, '\\');
    // holds indexes of slashes
    int idxs[toccr];
    
    if (toccr > 0)
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
