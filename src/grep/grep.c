#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <unistd.h>

#include "../../utils/str-utils.h"
#include "../../utils/colors.h"

#define USAGEMSG "Usage: grep [OPTIONS] <FILE> <PATTERN>\n"

void readDir(const char *path, const char *pattern);
void readFile(const char *path, const char *pattern);

int main(int argc, char const *argv[])
{
    char *path = ".";
    int opt;
    // TODO - implement all options
    // read options
    while ((opt = getopt(argc, argv, "lfh")) != -1)
    {
        switch (opt)
        {
            case 'h': break; // help
            case 'c': break; // count how many types pattern appears
            case 'i': break; // case-insensitive
            case 'l': break; // show line number
            case 'f': break; // show full line
            case 'p': break; // specify path (probably will remove)
            case 'w': break; // seperate word (only whole)
            case 'r':
            case 'R': break; // look in current dir and all subdirs
            case 'F': break; // find all lines with pattern (alias - fgrep)
            default:
                printf("Error: unknown option %c!\n", optopt);
                printf(USAGEMSG);
                return 1;
        }
    }

    // count all non-options
    int noptc[3];
    for(int i = 0; optind < argc; optind++)
    {
        printf("%d: %s\n", optind, argv[optind]);
    } 

    const char *pattern = argv[optind];
    
    // check for all required args
    if (optind < 2)
    {
        printf("Error: missing arguments!");
        printf(USAGEMSG);
        return 1;
    }

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
    if (prth) printf("\n");
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