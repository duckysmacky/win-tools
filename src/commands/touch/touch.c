#include "touch.h"

int main(int argc, char const *argv[])
{
    FILE *file;
    Opts opts = Opts_default;

    // read options
    int opt;
    while ((opt = getopt(argc, (char * const*) argv, OPTION_FLAGS)) != -1)
    {
        switch (opt)
        {
            // case 'h': break; // TODO - show help
            case 'a':
            case 'm':
            case 'd':
            case 'r':
            case 'c':
            default:
                printf("error: unknown option \"%c\"!\n", optopt);
                printf("do ls --help for help\n");
                printf(MSG_USAGE);
                return 1;
        }
    }
    if (argc < 2)
    {
        printf("missing arguments! usage: touch <FILE>");
        return 1;
    }

    const char *fpath = argv[1];
    int sloccr = stroccr(fpath, '/') + stroccr(fpath, '\\'); // total occurences of slashes
    int slpos[sloccr], j = 0; // indexes of slashes
    for (int i = 0; i < strlen(fpath); i++)
    {
        if (fpath[i] == '/' || fpath[i] == '\\')
        {
            slpos[j] = i; // add the index of a slash
            j++;
        }
    }

    int slposLen = arrlen(slpos);
    if (slposLen > 0)
    {
        // checking if full path exists, if not creating each dir
        for (int i = 0; i < slposLen; i++) // for each index of slash
        {
            int slidx = slpos[i]; // slash index
            char *dirpath = malloc((slidx + 1) * sizeof(char));
            for (int j = 0; j < slidx; j++) // write dir name (until a slash)
            {
                dirpath[j] = fpath[j];
            }
            dirpath[slidx] = '\0';

            if (opendir(dirpath) == NULL) // if dir doesnt exist 
            {
                mkdir(dirpath);
            }

            free(dirpath);
        }
    }

    // create the file itself
    file = fopen(fpath, "w");
    fclose(file);

    return 0;
}
