#include "head.h"

int main(int argc, char const *argv[])
{
    Opts opts = Opts_default;
    int opt, i;

    // read options
    while ((opt = getopt(argc, (char * const *) argv, OPTION_FLAGS)) != -1)
    {
        switch (opt)
        {
            // case 'h': break; // TODO - show help
            case 'q': opts.q = true; break;
            case 'v': opts.v = true; break;
            case 'n': {
                if (isnumber(optarg))
                {
                    opts.n = atoi(optarg);
                    break;
                }
                else
                {
                    printf("Error: supplied argument \"%s\" is not a number!\n", optarg);
                    printf(MSG_HELP);
                    return 1;
                }
            }
            case 'c': {
                if (isnumber(optarg))
                {
                    opts.c = atoi(optarg);
                    break;
                }
                else
                {
                    printf("Error: supplied argument \"%s\" is not a number!\n", optarg);
                    printf(MSG_HELP);
                    return 1;
                }
            }
            default:
                printf("Error: unknown option \"%c\"!\n", optopt);
                printf(MSG_USAGE);
                printf(MSG_HELP);
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

    // if there are multiple files
    if (i > 1) opts.v = true;

    // for each passed path
    for (i = 0; i < arrlen(noptc); i++)
    {
        readFile(noptc[i], &opts);
    }

    return 0;
}

void readFile(char *path, Opts *opts)
{
    FILE *file;
    char line[1024], *filename;
    int nline;

    file = fopen(path, "r");
    if (file == NULL)
    {
        printf("Error reading file \"%s\"!\n", path);
        fclose(file);
        return;
    }

    // print file name
    if (opts->v && !opts->q) printf("==> %s <==\n", path);

    // default number of lines
    if (opts->n == 0) opts->n = 10;
    
    nline = 1;
    while (fgets(line, 1024, file) && nline <= opts->n)
    {
        // printf("%llu | %s", strlen(line), line);
        printf("%s", line);
        // if (line[strlen(line)] != '\n') printf("\n");
        nline++;
    }

    fclose(file);
    return;
}