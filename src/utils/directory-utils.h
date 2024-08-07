#ifndef DIRECTORY_UTILS_H
#define DIRECTORY_UTILS_H

#include <Windows.h>
#include <tchar.h> 
#include <stdio.h>
#include <strsafe.h>

typedef struct DIRECTORY_T {
    HANDLE handle;
    LPWIN32_FIND_DATAA findData;
    int firstEntry;  // Flag to check if we are reading the first entry
} DIRECTORY;

typedef struct ENTRY_T {
    char name[MAX_PATH];
} ENTRY;

DIRECTORY* openDir(const char* dirPath);
ENTRY* nextEntry(DIRECTORY* dir);
int closeDir(DIRECTORY* dir);

#endif // !DIRECTORY_UTILS_H