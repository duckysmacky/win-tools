#include "Directory.h"

#include <iostream>
#include <vector>

utils::fs::Directory::Directory(const std::string &path)
{
    char directoryPath[MAX_PATH];
    sprintf_s(directoryPath, "%s\\*", path.c_str());

    handle = FindFirstFileA(directoryPath, findData);
    if (handle == INVALID_HANDLE_VALUE)
    {
        std::cerr << "Error: unable to open directory \"" << path << "\" (" << GetLastError() << ")" << std::endl;
    }
}

utils::fs::Directory::~Directory()
{
    if (!FindClose(handle))
    {
        std::cerr << "Error: unable to close directory handle" << std::endl;
    }
}

std::vector<utils::fs::Entry> utils::fs::Directory::getEntries() const
{
    std::vector<Entry> entries;

    do
    {
        entries.push_back(Entry{ findData->cFileName, findData->cAlternateFileName });
    }
    while (FindNextFileW(handle, (LPWIN32_FIND_DATAW) findData));

    return entries;
}