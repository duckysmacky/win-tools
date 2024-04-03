#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../../utils/str-utils.h"
#include "../../utils/colors.h"

// TODO - search for pattern in file, output line number
// TODO - search in whole dir, output filename

int main(int argc, char const *argv[])
{
    if (argc < 3)
    {
        printf("missing arguments! usage: grep <PATTERN> <FILE>");
        return 1;
    }

    const char *pattern = argv[1];
    const char *fpath = argv[2];
    FILE *file = fopen(fpath, "r");

    if (file == NULL)
    {
        printf("error: file doesn't exist!");
        return 1;
    }

    char line[256];
    int nline = 1;
    while (fgets(line, sizeof(line), file))
    {
        if (strstr(line, pattern))
        {
            // buff for colored pattern word
            char *cpattern = malloc(
                (sizeof(pattern) * sizeof(char) + 
                (2 * sizeof(COLOR_GREEN) * sizeof(char) + 1))
            );
            sprintf(cpattern, "%s%s%s", COLOR_GREEN, pattern, COLOR_RESET);
            strrplc(line, 256, pattern, cpattern);
            printf("%i %s", nline, line);
            free(cpattern);
        }
        nline++;
    }

    return 0;
}
