#include "head.h"

int main(int argc, char const *argv[])
{
    FLAGS flags = FLAGS_DEFAULT;

    int flag;
    while ((flag = getNextFlag(argc, argv, OPTION_FLAGS)) != -1)
    {
        switch (flag)
        {
            // case 'h': break; // TODO - show help
            case 'q': flags.q = true; break;
            case 'v': flags.v = true; break;
            case 'n': {
                if (isnumber(optionArgument))
                {
                    flags.n = atoi(optionArgument);
                    break;
                }
                else
                {
                    fprintf(stderr, "Error: supplied argument \"%s\" is not a number\n", optionArgument);
                    printf(MESSAGE_HELP);
                    return -1;
                }
            }
            case 'c': {
                if (isnumber(optionArgument))
                {
                    flags.c = atoi(optionArgument);
                    break;
                }
                else
                {
                    fprintf(stderr, "Error: supplied argument \"%s\" is not a number\n", optionArgument);
                    printf(MESSAGE_HELP);
                    return -1;
                }
            }
            default:
                fprintf(stderr, "Error: unknown option \"%c\"\n", optionFlag);
                printf(MESSAGE_USAGE);
                return -1;
        }
    }

    // holds all args
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
        fprintf(stderr, "Error: missing 1 argument!\n");
        printf(MESSAGE_USAGE);
        return -1;
    }

    // if there are multiple files
    if (argCount > 1) flags.v = true;

    // for each passed path
    for (argCount = 0; argCount < arrlen(args); argCount++)
    {
        readFile(args[argCount], &flags);
    }

    return 0;
}

void readFile(char *path, FLAGS *opts)
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