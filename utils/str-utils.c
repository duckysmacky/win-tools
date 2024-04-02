#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "str-utils.h"

// str = "abcd" (4)
// chars = "ef" (2)
// total = 6
// f = 5

int strapnd(char *str, char c) {
    size_t size = strlen(str);
    
    str = malloc(size + 2);

    str[size] = c;
    str[size + 1] = '\0';

    printf("%s\n", str);

    return 0;
}