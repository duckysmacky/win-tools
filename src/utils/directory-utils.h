#ifndef DIRECTORY_UTILS_H
#define DIRECTORY_UTILS_H

#include <strsafe.h>

#include "framework.h"

typedef struct T_DIRECTORY {
    HANDLE handle;
    WIN32_FIND_DATA findData;
    int firstEntry;  // Flag to check if we are reading the first entry
} DIRECTORY;

typedef struct T_ENTRY {
    char name[MAX_PATH];
} ENTRY;

DIRECTORY* openDir(const char* dirPath);
ENTRY* nextEntry(DIRECTORY* dir);
int closeDir(DIRECTORY* dir);

#endif // !DIRECTORY_UTILS_H