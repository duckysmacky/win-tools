#ifndef STR_UTILS
#define STR_UTILS

#include <string.h>

/*
    DOESNT WORK AS INTENDED
    Adds chars to the end of the string
    @param str string to append to
    @param c char to append
    @return status code
*/
char* strjoin(char *str1, char *str2);

/*
    Searches the string for characters
    @param buff location to write the found indexes
    @param str string to search in
    @param c char to search
    @return true if found any
*/
int strfnd(int *buff, char *str, char c);

/*
    Counts occurences of a char in string
    @param str string to search in
    @param c char to search
    @return occurences of c in str
*/
size_t stroccr(const char *str, const char c);

#endif