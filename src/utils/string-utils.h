#ifndef STRING_UTILS_H
#define STRING_UTILS_H

#include <string>

namespace utils
{
    bool isNumber(const std::string &str);
    std::string toLowercase(const std::string& str);
    std::string toUppercase(const std::string& str);
}

#ifdef __cplusplus
extern "C" {
#endif 
    /*
        DOESNT WORK AS INTENDED
        Adds characters to the end of the string
        @param str string to append to
        @param c char to append
        @return status code
    */
    char* joinStrings(char* str1, char* str2);
    /*
        Searches the string for characters
        @param buff location to write the found indexes
        @param str string to search in
        @param c char to search
        @return true if found any
    */
    int findChar(int* buff, char* str, char c);
    /*
        Counts occurences of a sting in string
        @param str source string
        @param c string to search in source
        @return occurences of c in str
    */
    int countCharOccurences(const char* str, const char c);
    /*
        Replaces a substring in a string
        @param str source
        @param size buffer size
        @param substr substring to replace
        @param newstr what to replace with
        @return updated string if replaced, else NULL
    */
    char* replaceString(char* str, size_t size, const char* substr, const char* newstr);
    /*
        Converts all characters in a string to lowercase
        @param buff buffer to write converted string
        @param str original string
    */
    void stringToLower(char* buff, char* str);
    /*
        Converts all characters in a string to uppercase
        @param buff buffer to write converted string
        @param str original string
    */
    void stringToUpper(char* buff, char* str);
    /*
        Get the last n characters from the string
        @param str string
        @param n amount of characters to get
        @return last n characters of string
    */
    char* getSuffix(char* str, int n);
#ifdef __cplusplus
}
#endif

#endif