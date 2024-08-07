#include "head.h"

int main(int argc, char *argv[])
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
    char* args[64] = {0};
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

    // if there are multiple files
    if (argCount > 1) flags.v = true;

    // for each passed path
    for (argCount = 0; argCount < arrlen(args); argCount++)
    {
        if (readFile(args[argCount], &flags) != 0) return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}

int readFile(const char *filePath, FLAGS *opts)
{
    FILE **file = malloc(sizeof(FILE));
    if (file == NULL)
    {
        fprintf(stderr, "Error: allocation failed\n");
        free(file);
        return -1;
    }

    if (!fopen_s(file, filePath, "r"))
    {
        fprintf(stderr, "Error: unable to open file at \"%s\"\n", filePath);
        free(file);
        return -1;
    }

    // print file name
    if (opts->v && !opts->q) printf("==> %s <==\n", filePath);

    // default number of lines
    if (opts->n == 0) opts->n = 10;
    
    char line[1024];
    int lineNumber = 1;
    while (fgets(line, 1024, *file) && lineNumber <= opts->n)
    {
        printf("%s", line);
        lineNumber++;
    }

    free(file);
    return 0;
}