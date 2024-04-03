#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>

int main(int argc, char const *argv[])
{
    FILE *file;
    if (argc < 2)
    {
        printf("Error: missing arguments <filepath>");
        return 1;
    }

    const char *fpath = argv[1];
    int slpos[32]; // holds indexes of slashes
    int j = 0;
    for (int i = 0; i <= strlen(fpath); i++)
    {
        if (fpath[i] == '/' || fpath[i] == '\\')
        {
            printf("fpath s %u\n", fpath[i]);
            slpos[j] = i; // add the indexes of slashes
            j++;
        }
    }


    printf("slpos ");
    for (size_t x = 0; x < 32; x++) {  }

    // checking if full path exists, if not creating one
    size_t slposLen = sizeof(slpos) / sizeof(int);
    if (slposLen != 0)
    {
        for (int i = 0; i < slposLen; i++) // for each index of slash
        {
            // reading path up to slash index
            char *dirpath = malloc(i * sizeof(char) + 1);
            for (int s = 0; s < i; s++) // for each dir to to next slash
            {
                dirpath[s] = fpath[s];
            }

            printf("dirpath: %s\n", dirpath);

            if (opendir(dirpath) == NULL) // if dir doesnt exist 
            {
                // mkdir(dirpath);
                printf("mkdir\n");
            }
        }
    }

    file = fopen(fpath, "w");
    fclose(file);

    return 0;
}
