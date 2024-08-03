#ifndef ARRAY_UTILS_H
#define ARRAY_UTILS_H

#include <stdlib.h>
#include <string.h>

/*
    Searches for a string in array
    @param arr array to search in
    @param size size of the array
    @param str string to search in array
    @return status code
*/
int strinarr(char *arr[], size_t size, char *str);

/*
    Get length of array
*/
#define arrlen(arr) (sizeof(arr) / sizeof(*arr))

#endif