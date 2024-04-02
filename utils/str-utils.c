#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "str-utils.h"

char* strjoin(char *str1, char *str2) {
    char* str = (char*) malloc((strlen(str1) + strlen(str2) + 1) * sizeof(char));

    strcpy(str, str1);
    strcat(str, str2);

    return str;
}