#include "string-utils.h"

#include <string>

#include <string.h>

#include "array-utils.h"

using namespace std;

namespace utils
{
    bool isNumber(const std::string& str)
    {
        string::const_iterator iter = str.begin();
        while (iter != str.end() && isdigit(*iter)) ++iter;
        return !str.empty() && iter == str.end();
    }
}


char* joinStrings(char *str1, char *str2)
{
    char *str = (char*) malloc(sizeof(str1) + sizeof(str2));

    strcpy_s(str, sizeof(str1), str1);
    strcat_s(str, sizeof(str2), str2);

    return str;
}

int findChar(int *buff, char *str, char c)
{
    int j = 0;
    for (int i = 0; i < strlen(str); i++)
    {
        if (str[i] == c)
        {
            buff[j] = i;
            j++;
        }
    }

    if (sizeof(buff) == 0)
    {
        return 1;
    }

    return 0;
}

int countCharOccurences(const char *str, const char c)
{
    int i;
    for (i = 0; str[i]; str[i] == c ? i++ : *str++);
    return i;
}

char* replaceString(char *str, size_t size, const char *substr, const char *newstr)
{
    char *p = strstr(str, substr); // pointer to the substr in str
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

void stringToLower(char *buff, char *str)
{
    size_t l = strlen(buff);
    for (int i = 0; i < l; i++)
    {
        buff[i] = tolower(str[i]);
    }
    buff[l] = '\0';
}

void stringToUpper(char *buff, char *str)
{
    size_t l = strlen(buff);
    for (int i = 0; i < l; i++)
    {
        buff[i] = toupper(str[i]);
    }
    buff[l] = '\0';
}

char* getSuffix(char *str, int n)
{
    size_t len = strlen(str);
    return (char *) str + len - n;
}