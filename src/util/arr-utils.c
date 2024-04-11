#include <stdlib.h>
#include <string.h>

int strinarr(char *arr[], size_t size, char *str) {
    for(size_t i = 0; i < size / sizeof(*arr); i++) {
        if(strcmp(arr[i], str)) return 1;
    }
    return 0;
}