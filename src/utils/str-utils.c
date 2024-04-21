#include "../include/str-utils.h"

char* strjoin(char *str1, char *str2) {
    char* str = (char*) malloc((strlen(str1) + strlen(str2) + 1) * sizeof(char));

    strcpy(str, str1);
    strcat(str, str2);

    return str;
}

int strfnd(int *buff, char *str, char c) {
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

int stroccr(const char *str, const char c) {
    int i;
    for (i = 0; str[i]; str[i] == c ? i++ : *str++);
    return i;
}

char* strrplc(char *str, size_t size, const char *substr, const char *newstr)
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

void strtolwr(char *buff, char *str)
{
    int l = strlen(buff);
    for (int i = 0; i < l; i++)
    {
        buff[i] = tolower(str[i]);
    }
    buff[l] = '\0';
}

void strtoupr(char *buff, char *str)
{
    int l = strlen(buff);
    for (int i = 0; i < l; i++)
    {
        buff[i] = toupper(str[i]);
    }
    buff[l] = '\0';
}