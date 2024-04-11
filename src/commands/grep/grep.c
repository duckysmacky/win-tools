// TODO - implement all options
// TODO - multiple file support

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <unistd.h>

#include "../../headers/arr-utils.h"
#include "../../headers/str-utils.h"
#include "../../headers/colors.h"

#define USAGEMSG "Usage: grep [OPTIONS] <PATTERN> <PATH>\n"

void readDir(const char *path, const char *pattern);
void readFile(const char *path, const char *pattern);

int main(int argc, const char *argv[])
{
    // read options
    int opt;
    while ((opt = getopt(argc, (char * const*) argv, "lfh")) != -1)
    {
        switch (opt)
        {
            case 'h': break; // help
            case 'c': break; // print line count of the matched pattern
            case 'i': break; // ignore-case
            case 'l': break; // display filenames only
            case 'n': break; // show line numbers
            case 'v': break; // print all lines which didnt match
            case 'e': break; // regular expression to search
            case 'f': break; // take pattern from file
            case 'w': break; // match whole word only
            case 'o': break; // print only matching parts of the lines
            default:
                printf("Error: unknown option %c!\n", optopt);
                printf(USAGEMSG);
                return 1;
        }
    }

    // holds all non-options (pattern and path)
    char *noptc[2];
    int i = 0;
    for(; optind < argc; optind++)
    {
        noptc[i] = (char *) argv[optind];
        printf("%d: %s\n", optind, argv[optind]);
        i++;
    } 

    // check for all required args
    if (i < 2)
    {
        printf("Error: missing %d argument[s]!\n", 2 - i);
        printf(USAGEMSG);
        return 1;
    }

    const char *pattern = noptc[0];
    const char *path = noptc[1];

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