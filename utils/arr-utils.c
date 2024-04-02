#include <stdlib.h>
#include <string.h>

int strinar(char *arr[], size_t size, char *str) {
    for(size_t i = 0; i < size / sizeof(*arr); i++) {
        if(strcmp(arr[i], str)) return 1;
    }
    return 0;
}