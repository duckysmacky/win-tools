#include "./arrays.h"

#include <string.h>

int stringInArray(char *arr[], size_t size, char *str)
{
    for (size_t i = 0; i < size / sizeof(*arr); i++)
    {
        if (strcmp(arr[i], str)) return 1;
    }
    return 0;
}