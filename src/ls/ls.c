#include <stdio.h>
#include <string.h>
#include <dirent.h>

int main(int argc, char const *argv[])
{
    DIR *dir;
    struct dirent *dEntry;

    if (argc > 1) dir = opendir(argv[1]);
    else dir = opendir("./");

    if (dir == NULL)
    {
        printf("Error opening directory!\n");
        return 1;
    }

    while ((dEntry = readdir(dir)) != NULL)
    {
        printf("%s\n", dEntry -> d_name);
    }

    if (closedir(dir) == -1)
    {
        printf("Error opening directory!\n");
        return 1;
    }

    return 0;
}
