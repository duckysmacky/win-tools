#include <stdio.h>
#include <string.h>

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
            printf("%i %s", nline, line);
        }
        nline++;
    }

    return 0;
}
