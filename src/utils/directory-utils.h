#ifndef DIRECTORY_UTILS_H
#define DIRECTORY_UTILS_H

#include <Windows.h>

typedef struct DIRECTORY_T {
    HANDLE handle;
    LPWIN32_FIND_DATAA findData;
    int firstEntry;  // Flag to check if we are reading the first entry
} DIRECTORY;

typedef struct ENTRY_T {
    char name[MAX_PATH];
} ENTRY;

#ifdef __cplusplus
extern "C" {
#endif 

        DIRECTORY* openDir(const char* dirPath);
        ENTRY* nextEntry(DIRECTORY* dir);
        int closeDir(DIRECTORY* dir);

#ifdef __cplusplus
}
#endif 

#endif // !DIRECTORY_UTILS_H