#include "option-utils.h"

char* optionArgument = NULL;
int optionIndex = 1, optionError = 1;
char optionFlag;

char getNextFlag(int argc, char* const argv[], const char* allOptionsString) {
    static char* next = NULL;
    
    if (optionIndex == 1)
    {
        next = NULL;
    }

    optionArgument = NULL;
    if (next == NULL || *next == '\0')
    {
        if (optionIndex == argc || argv[optionIndex][0] != '-' || argv[optionIndex][1] == '\0')
        {
            next = NULL;
            return -1;
        }

        if (argv[optionIndex][1] == '-' && argv[optionIndex][2] == '\0')
        {
            optionIndex++;
            next = NULL;
            return -1;
        }

        next = argv[optionIndex] + 1;
        optionIndex++;
    }

    optionFlag = *next++;

    const char* option = strchr(allOptionsString, optionFlag);
    if (option == NULL || optionFlag == ':')
    {
        if (*next == '\0')
        {
            optionIndex++;
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
            optionIndex++;
        }
        else if (optionIndex < argc)
        {
            optionArgument = argv[optionIndex];
            optionIndex++;
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