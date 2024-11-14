#include "Directory.h"

#include <iostream>
#include <vector>

namespace utils::fs
{
    Directory::Directory(const std::string& path)
        : m_handle(nullptr), m_size(0)
    {
        std::string dirFilesPath = path + "\\*";

        HANDLE m_handle = FindFirstFileExA(dirFilesPath.c_str(), FindExInfoStandard, &m_findData, FindExSearchNameMatch, NULL, FIND_FIRST_EX_LARGE_FETCH);
        if (m_handle == INVALID_HANDLE_VALUE)
        {
            std::cerr << "Error getting directory handle for \"" << path << "\" (" << GetLastError() << ")" << std::endl;
            return;
        }

        while (FindNextFileA(m_handle, &m_findData))
        {
            m_entries.push_back(Entry {
                m_findData.cFileName,
                m_findData.cAlternateFileName
            });
        }

        m_size = getDirSize(path);
    }

    Directory::~Directory()
    {
        FindClose(m_handle);
    }

    int64_t Directory::getDirSize(const std::string& path)
    {
        if (path == "." || path == "..") return 0;
        
        WIN32_FIND_DATAA dirFindData{};
        HANDLE dirHandle = FindFirstFileExA(path.c_str(), FindExInfoBasic, &dirFindData, FindExSearchNameMatch, NULL, FIND_FIRST_EX_ON_DISK_ENTRIES_ONLY);
        if (dirHandle == INVALID_HANDLE_VALUE)
        {
            std::cerr << "Error getting directory handle for \"" << path << "\" (" << GetLastError() << ")" << std::endl;
            return 0;
        }

        LARGE_INTEGER dirSize{};
        while (FindNextFileA(dirHandle, &dirFindData))
        {
            LARGE_INTEGER fileSize = { 0 };
            std::string fileName = dirFindData.cFileName;

            if (fileName == "." || fileName == "..") continue;

            if (dirFindData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
            {
                std::string dirPath = path.c_str();

                LONGLONG dirSizeQuad = (fileName == "." || fileName == "..") ? 0 : getDirSize(dirPath);
                dirSize.QuadPart += dirSizeQuad;
                std::cout << "Size of \"" << fileName << "\": " << dirSizeQuad << std::endl;
            }
            else
            {
                fileSize.LowPart = dirFindData.nFileSizeLow;
                fileSize.HighPart = dirFindData.nFileSizeHigh;
                dirSize.QuadPart += fileSize.QuadPart;
                printf("file: %s | size: %llu\n", fileName, fileSize.QuadPart);
            }
        } 

        std::cout << "Total size of \"" << path << "\" found: " << dirSize.QuadPart << std::endl;
        FindClose(dirHandle);
        return dirSize.QuadPart;
    }

    std::vector<Directory::Entry> Directory::entries() const
    {
        return m_entries;
    }

    int64_t Directory::size() const
    {
        return m_size;
    }
}