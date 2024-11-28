#include "Directory.h"

#include <iostream>
#include <vector>
#include <format>

namespace utils::fs
{
    Directory::Directory(const std::string& path)
        : m_path(path)
    {
        std::string dirFilesPath = path + "\\*";

        m_handle = FindFirstFileExA(dirFilesPath.c_str(), FindExInfoStandard, &m_findData, FindExSearchNameMatch, NULL, FIND_FIRST_EX_LARGE_FETCH);
        if (m_handle == INVALID_HANDLE_VALUE)
        {
            std::cerr << "Error getting directory handle for \"" << path << "\" (" << GetLastError() << ")" << std::endl;
            return;
        }

        while (FindNextFileA(m_handle, &m_findData))
        {
            Entry entry;
            LARGE_INTEGER fileSize{};
            entry.name = m_findData.cFileName;
            fileSize.HighPart = m_findData.nFileSizeHigh;
            fileSize.LowPart = m_findData.nFileSizeLow;
            entry.size = fileSize.QuadPart;
            entry.isDir = (m_findData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY);

            m_entries.push_back(entry);
        }
    }

    Directory::~Directory()
    {
        FindClose(m_handle);
    }

    std::vector<Directory::Entry> Directory::entries() const
    {
        return m_entries;
    }

    int64_t Directory::size() const
    {
        return getDirSize(m_path);
    }

    int64_t Directory::getDirSize(const std::string& path) const
    {
        if (path == "." || path == "..") return 0;
        
        std::string dirFilesPath = path + "\\*";

        WIN32_FIND_DATAA dirFindData{};
        //HANDLE dirHandle = FindFirstFileExA(dirFilesPath.c_str(), FindExInfoStandard, &dirFindData, FindExSearchNameMatch, NULL, FIND_FIRST_EX_LARGE_FETCH);
        HANDLE dirHandle = FindFirstFileExA(dirFilesPath.c_str(), FindExInfoBasic, &dirFindData, FindExSearchNameMatch, NULL, FIND_FIRST_EX_ON_DISK_ENTRIES_ONLY);
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
                std::string dirPath = std::format("{}/{}", path, fileName);

                LONGLONG dirSizeQuad = (fileName == "." || fileName == "..") ? 0 : getDirSize(dirPath);
                dirSize.QuadPart += dirSizeQuad;
            }
            else
            {
                fileSize.LowPart = dirFindData.nFileSizeLow;
                fileSize.HighPart = dirFindData.nFileSizeHigh;
                dirSize.QuadPart += fileSize.QuadPart;
            }
        } 

        FindClose(dirHandle);
        return dirSize.QuadPart;
    }

}