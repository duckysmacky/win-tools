#ifndef UTILS_COMMON_ARRAYS_H
#define UTILS_COMMON_ARRAYS_H

/* Get length of array */
#define arrlen(arr) (sizeof(arr) / sizeof(*arr))

#ifdef __cplusplus
extern "C" {
#endif 
        /*
            Searches for a c-string in array
            @param arr array to search in
            @param size size of the array
            @param str string to search in array
            @return status code
        */
        int stringInArray(char* arr[], size_t size, char* str);
#ifdef __cplusplus
}
#endif 

#endif // !UTILS_COMMON_ARRAYS_H