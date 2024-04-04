#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>

#include "../../utils/str-utils.h"
#include "../../utils/colors.h"

// TODO - options support

void readFile(const char *path, const char *pattern)
{
    FILE *file = fopen(path, "r");
    if (file == NULL)
    {
        printf("error reading file!\n");
        fclose(file);
        return;
    }
    
    char line[256];
    int nline = 1, prth = 0;
    while (fgets(line, 256, file))
    {
        if (strstr(line, pattern))
        {
            if (!prth) // print filepath at the top
            {
                prtblue("%s\n", path);
                prth = 1;
            }
            
            // buff for colored pattern word
            char *cpattern = malloc(
                strlen(pattern) * sizeof(char) + 
                (2 * sizeof(COLOR_GREEN) + sizeof(char))
            );

            sprintf(cpattern, "%s%s%s", COLOR_GREEN, pattern, COLOR_RESET);
            strrplc(line, 256, pattern, cpattern);
            printf("%i %s", nline, line);
            free(cpattern);
        }
        nline++;
    }
    printf("\n");
    fclose(file);
    return;
}

void readDir(const char *path, const char *pattern)
{
    struct dirent *dEntry;
    DIR *dir = opendir(path);

    while ((dEntry = readdir(dir)))
    {
        char *ename = malloc((strlen(dEntry -> d_name) + 1) * sizeof(char)); // entry name
        strcpy(ename, dEntry -> d_name);
        ename[strlen(ename)] = '\0';

        // ignore . and .. files
        if (!strcmp(ename, ".") || !strcmp(ename, "..")) continue;

        char *fpath = malloc( // holds dir path + entry name
            strlen(path) * sizeof(char) +
            (strlen(ename) + 1) * sizeof(char)
        );
        sprintf(fpath, "%s%s", path, ename);

        if (opendir(fpath))
        {
            strcat(fpath, "/");
            readDir(fpath, pattern);
        }
        else if (fopen(fpath, "r"))   
        {
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
    return;
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
        if (stroccr(path, '/') > 0 || stroccr(path, '\\') > 0) // if there are slashes
        {
            readDir(path, pattern);
        }
        else
        {
            char *dpath = malloc(sizeof(strlen(path) + 2) * sizeof(char));
            sprintf(dpath, "%s/", path);
            readDir(dpath, pattern);
            free(dpath);
        }
    }
    else
    {
        printf("error: file doesn't exist!");
        return 1;
    }
    
    return 0;
}
