#ifndef UTILS_COMMON_STRINGS_H
#define UTILS_COMMON_STRINGS_H

#include <string>

namespace utils
{
    bool isNumber(const std::string &str);
    std::string toLowercase(const std::string& str);
    std::string toUppercase(const std::string& str);
    /*
        Searches the string for characters
        @param buff location to write the found indexes
        @param str string to search in
        @param c char to search
        @return true if found any
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
        Get the last n characters from the string
        @param str string
        @param n amount of characters to get
        @return last n characters of string
    */
    char* getSuffix(char* str, int n);

}

#endif // !UTILS_COMMON_STRINGS_H