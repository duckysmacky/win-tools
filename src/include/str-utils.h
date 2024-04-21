#ifndef STR_UTILS
#define STR_UTILS

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#include "../include/arr-utils.h"

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

/*
    Converts all characters in a string to lowercase
    @param buff buffer to write converted string
    @param str original string
*/
void strtolwr(char *buff, char *str);

/*
    Converts all characters in a string to uppercase
    @param buff buffer to write converted string
    @param str original string
*/
void strtoupr(char *buff, char *str);

#endif