#include "string-utils.h"

#include <string>

#include <string.h>

namespace utils
{
    bool isNumber(const std::string& str)
    {
        std::string::const_iterator iter = str.begin();
        while (iter != str.end())
        {
            if (!isdigit(*iter)) return false;
            ++iter;
        }
        return !str.empty() && iter == str.end();
    }

    std::string toLowercase(const std::string& str)
    {
        std::string result = "";

        for (char ch : str)
            result += tolower(ch);

        return result;
    }

    std::string toUppercase(const std::string& str)
    {
        std::string result = "";

        for (char ch : str)
            result += toupper(ch);

        return result;
    }

    int countCharOccurences(const char* str, const char c)
    {
        int i;
        for (i = 0; str[i]; str[i] == c ? i++ : *str++);
        return i;
    }

    char* replaceString(char* str, size_t size, const char* substr, const char* newstr)
    {
        char* p = strstr(str, substr); // pointer to the substr in str
        if (p == NULL) return NULL;

        // check if size is enough
        if (size < strlen(str) - strlen(substr) + (strlen(newstr)) + 1) {
            printf("Buffer size is too small!\n");
            return NULL;
        }

        // move
        memmove(
            p + strlen(newstr), // to
            p + strlen(substr), // from
            strlen(p) - strlen(substr) + 1 // size
        );

        memcpy(p, newstr, strlen(newstr));
        return p + strlen(newstr);
    }

    char* getSuffix(char* str, int n)
    {
        size_t len = strlen(str);
        return (char*)str + len - n;
    }
}