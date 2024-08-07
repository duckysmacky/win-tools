#include "directory-utils.h"

DIRECTORY* openDir(const char* dirPath)
{
    DIRECTORY* dir = (DIRECTORY*) malloc(sizeof(DIRECTORY));
    if (dir == NULL)
    {
        fprintf(stderr, "Error: memory allocation failed\n");
        return NULL;
    }

    char dirFilePath[MAX_PATH];
    snprintf(dirFilePath, MAX_PATH, dirPath);
    snprintf(dirFilePath, MAX_PATH, TEXT("\\*"));

    dir->handle = FindFirstFileA(dirFilePath, &dir->findData);
    if (dir->handle == INVALID_HANDLE_VALUE)
    {
        fprintf(stderr, "Error: unable to open directory \"%s\"\n", dirPath);
        free(dir);
        return NULL;
    }

    dir->firstEntry = 1;
    return dir;
}

ENTRY* nextEntry(DIRECTORY* dir)
{
    if (dir == NULL)
    {
        return NULL;
    }

    ENTRY* entry = (ENTRY*) malloc(sizeof(ENTRY));
    if (entry == NULL)
    {
        fprintf(stderr, "Error: memory allocation failed\n");
        return NULL;
    }

    if (dir->firstEntry)
    {
        dir->firstEntry = 0;
        strncpy(entry->name, dir->findData.cFileName, MAX_PATH);
    }
    else
    {
        if (!FindNextFile(dir->handle, &dir->findData))
        {
            free(entry);
            return NULL;
        }

        strncpy(entry->name, dir->findData.cFileName, MAX_PATH);
    }

    return entry;
}

int closeDir(DIRECTORY* dir)
{
    if (dir == NULL)
    {
        return -1;
    }
    
    if (!FindClose(dir->handle))
    {
        fprintf(stderr, "Error: unable to close directory handle\n");
        return -1;
    }
    
    free(dir);
    return 0;
}