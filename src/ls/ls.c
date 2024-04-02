// Better ls

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>

#include "../../utils/str-utils.h"

int main(int argc, char const *argv[])
{
    const char *NAME_EXEPTIONS[] = {
        "Makefile"
    };

    DIR* dir;
    struct dirent* dEntry;

    if (argc > 1) dir = opendir(argv[1]); else dir = opendir("./");

    if (dir == NULL)
    {
        printf("Error opening directory!\n");
        return 1;
    }

    // TODO - check for dotfiles
    // TODO - sort in order
    // TODO - add coloring
    // TODO - make working exceptions
    while (dEntry = readdir(dir))
    {
        char* name = malloc(sizeof(dEntry -> d_name) + 1); // file name
        strcpy(name, dEntry -> d_name);
        // ignore . and ..
        if (!strcmp(name, ".") || !strcmp(name, "..")) {
            continue;
        }

        const char* ext = strrchr(name, '.'); // holds extention
        if (ext == NULL)
        {
            strcat(name, "/");
        }

        printf("%s ", name);
        free(name);
    }

    if (closedir(dir) == -1)
    {
        printf("Error opening directory!\n");
        return 1;
    }

    return 0;
}
