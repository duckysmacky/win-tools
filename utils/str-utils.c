#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "str-utils.h"
#include "arr-utils.h"

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

    if (arrlen(buff) == 0)
    {
        return 1;
    }

    return 0;
}

size_t stroccr(const char *str, const char c) {
    size_t i;
    for (i = 0; str[i]; str[i] == c ? i++ : *str++);
    return i;
}