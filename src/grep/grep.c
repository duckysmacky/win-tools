#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>

#include "../../utils/str-utils.h"
#include "../../utils/colors.h"

// TODO - options support
// TODO - search in whole dir, output filename

void readFile(const char *path, const char *pattern)
{
    printf("recieved filepath: %s with pattern %s\n", path, pattern);
    FILE *file;
    if ((file = fopen(path, "r")) == NULL) printf("error reading file at %s\n", path);
    
    char line[256];
    int nline = 1;
    while (fgets(line, sizeof(line), file))
    {
        printf("reading line: %s", line);
        if (strstr(line, pattern))
        {
            // buff for colored pattern word
            char *cpattern = malloc(
                sizeof(pattern) * sizeof(char) + 
                (2 * sizeof(COLOR_GREEN) * sizeof(char) + 1)
            );
            sprintf(cpattern, "%s%s%s", COLOR_GREEN, pattern, COLOR_RESET);
            strrplc(line, 256, pattern, cpattern);
            printf("%i %s", nline, line);
            free(cpattern);
        }
        nline++;
    }
    fclose(file);
}

void readDir(const char *path, const char *pattern)
{
    struct dirent *dEntry;
    char *dpath = malloc(sizeof(path) * sizeof(char) + 1);
    strcpy(dpath, path);
    // check for slashes, if none add them
    if (stroccr(path, '/') == 0 && stroccr(path, '\\') == 0) strcat(dpath, "/");
    DIR *dir = opendir(dpath);

    while (dEntry = readdir(dir))
    {
        char *ename = malloc((strlen(dEntry -> d_name) + 1) * sizeof(char)); // entry name
        strcpy(ename, dEntry -> d_name);
        // ignore . and .. files
        if (!strcmp(ename, ".") || !strcmp(ename, "..")) continue;
        printf("found entry: %s at dir %s\n", ename, dpath);

        char *fpath = malloc( // holds dir path + entry name
            sizeof(dpath) * sizeof(char) +
            sizeof(ename) * sizeof(char) + 2
        );

        sprintf(fpath, "%s%s", dpath, ename);

        if (opendir(fpath))
        {
            printf("going to dir: %s\n", ename);
            strcat(fpath, "/\0");
            readDir(fpath, pattern);
        }
        else if (fopen(fpath, "r"))   
        {
            printf("opening file: %s\n", fpath);
            strcat(fpath, "\0");
            readFile(fpath, pattern);
        }
        else
        {
            printf("error reading dir: %s\n", fpath);
            return;
        }
        free(fpath);
        free(ename);
    }
}

int main(int argc, char const *argv[])
{
    if (argc < 3)
    {
        printf("missing arguments! usage: grep <PATTERN> <FILE>");
        return 1;
    }

    const char *pattern = argv[1];
    const char *path = argv[2];

    if (fopen(path, "r"))
    {
        readFile(path, pattern);
    }
    else if (opendir(path))
    {
        readDir(path, pattern);
    }
    else
    {
        printf("error: file doesn't exist!");
        return 1;
    }
    
    return 0;
}
