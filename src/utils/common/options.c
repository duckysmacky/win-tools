// DEPRICATED

#include "./options.h"

#include <stdio.h>
#include <string.h>

char* optionArgument = NULL;
int argIndex = 1, optionError = 1;
char optionFlag;

char getNextFlag(int argc, const char* argv[], const char* allOptionsString) {
    static char* next = NULL;
    
    if (argIndex == 1)
    {
        next = NULL;
    }

    optionArgument = NULL;
    if (next == NULL || *next == '\0')
    {
        if (argIndex == argc || argv[argIndex][0] != '-' || argv[argIndex][1] == '\0')
        {
            next = NULL;
            return -1;
        }

        if (argv[argIndex][1] == '-' && argv[argIndex][2] == '\0')
        {
            argIndex++;
            next = NULL;
            return -1;
        }

        next = argv[argIndex] + 1;
        argIndex++;
    }

    optionFlag = *next++;

    const char* option = strchr(allOptionsString, optionFlag);
    if (option == NULL || optionFlag == ':')
    {
        if (*next == '\0')
        {
            argIndex++;
        }

        if (optionError && *allOptionsString != ':')
        {
            fprintf(stderr, "Unknown option '-%c'\n", optionFlag);
        }

        return '?';
    }

    if (option[1] == ':')
    {
        if (*next != '\0')
        {
            optionArgument = next;
            argIndex++;
        }
        else if (argIndex < argc)
        {
            optionArgument = argv[argIndex];
            argIndex++;
        }
        else
        {
            if (optionError && *allOptionsString != ':') {
                fprintf(stderr, "Option '-%c' requires an argument\n", optionFlag);
            }

            next = NULL;
            return ':';
        }

        next = NULL;
    }

    return optionFlag;
}