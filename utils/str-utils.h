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
    Counts occurences of a sting in string
    @param str source string
    @param c string to search in source
    @return occurences of c in str
*/
int stroccr(const char *str, const char c);

/*
    Replaces a substring in a string
    @param str source
    @param size buffer size
    @param substr substring to replace
    @param newstr what to replace with
    @returns updated string if replaced, else NULL
*/
char* strrplc(char *str, size_t size, const char *substr, const char *newstr);

#endif