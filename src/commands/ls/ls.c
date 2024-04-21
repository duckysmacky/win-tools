#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>

#include "../../include/arr-utils.h"
#include "../../include/colors.h"

int main(int argc, char const *argv[])
{
    char *NAME_EXEPTIONS[] = {
        "Makefile"
    };
    struct dirent* dEntry;
    DIR *dir = argc > 1 ? opendir(argv[1]) : opendir("./");

    if (dir == NULL)
    {
        printf("Error opening directory!\n");
        return 1;
    }

    // TODO - make files print in order
    while ((dEntry = readdir(dir)))
    {
        char* name = malloc((strlen(dEntry -> d_name) + 1) * sizeof(char)); // file name
        strcpy(name, dEntry -> d_name);
        // ignore . and .. files
        if (!strcmp(name, ".") || !strcmp(name, "..")) {
            continue;
        }

        const char* ext = strrchr(name, '.'); // holds file extention
        if (ext == NULL && strinarr(NAME_EXEPTIONS, sizeof(NAME_EXEPTIONS), name))
        { 
            prtgreen("%s/ ", name);
        }
        else if (((int)(ext - name)) == 0) // if index of the extention is 0
        { 
            prtblue("%s ", name);
        }
        else
        { 
            printf("%s ", name);
        }

        free(name);
    }

    closedir(dir);
    return 0;
}
