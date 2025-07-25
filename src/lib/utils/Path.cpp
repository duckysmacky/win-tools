#include <string>
#include <string_view>
#include <sstream>
#include <vector>
#include <format>
#include <optional>

#include <Windows.h>

#include "./Path.hpp"

namespace fs
{
    Path::Path(const std::string& path)
        : m_buffer(normalize(path))
    {
    }

    Path::Path(std::string_view path)
        : m_buffer(normalize(path.data()))
    {
    }

    Path::Path(const std::string segments[])
    {
        for (int i = 0; i < segments->length(); i++)
        {
            m_buffer += normalize('\\' + segments[i]);
        }
    }

    Path::operator std::string() const
    {
        return m_buffer;
    }

    Path::operator std::string_view() const
    {
        return m_buffer;
    }

    Path Path::join(const std::string& subpath) const
    {
        return Path(normalize(m_buffer + '\\' + subpath));
    }

    void Path::push(const std::string& subpath)
    {
        m_buffer += normalize('\\' + subpath);
    }

    std::string Path::pop()
    {
        size_t lastSlash_i = m_buffer.find_last_of('\\');
        std::string::iterator removed = m_buffer.begin() + lastSlash_i;
        m_buffer.erase(removed);
        return std::string(m_buffer.begin(), removed);
    }

    bool Path::exists() const
    {
        DWORD fileAttributes = GetFileAttributesA(m_buffer.c_str());

        return fileAttributes != INVALID_FILE_ATTRIBUTES;
    }

    bool Path::isDirectory() const
    {
        DWORD fileAttributes = GetFileAttributesA(m_buffer.c_str());

        if (fileAttributes != INVALID_FILE_ATTRIBUTES)
        {
            return fileAttributes & FILE_ATTRIBUTE_DIRECTORY;
        }
        else
        {
            return !fileExtension().has_value();
        }
    }

    bool Path::isFile() const
    {
        DWORD fileAttributes = GetFileAttributesA(m_buffer.c_str());

        if (fileAttributes != INVALID_FILE_ATTRIBUTES)
        {
            return !(fileAttributes & FILE_ATTRIBUTE_DIRECTORY);
        }
        else
        {
            return fileExtension().has_value();
        }
    }

    bool Path::isHidden() const
    {
        DWORD fileAttributes = GetFileAttributesA(m_buffer.c_str());

        if (fileAttributes != INVALID_FILE_ATTRIBUTES)
        {
            return fileAttributes & FILE_ATTRIBUTE_HIDDEN;
        }
        else
        {
            return fileRoot().at(0) == '.';
        }
    }

    void Path::setFile(const std::string& file)
    {
        if (m_buffer.empty())
        {
            m_buffer = normalize(file);
            return;
        }

        size_t lastSlash_i = m_buffer.find_last_of('\\');
        std::string::iterator fileStart = m_buffer.begin();
        if (lastSlash_i != std::string::npos)
        {
            fileStart += lastSlash_i + 1;
        }

        m_buffer.replace(fileStart, m_buffer.end(), file);
    }

    void Path::setFileName(const std::string& fileName)
    {
        if (m_buffer.empty())
        {
            m_buffer = normalize(fileName);
            return;
        }

        size_t lastSlash_i = m_buffer.find_last_of('\\');
        std::string::iterator nameStart = m_buffer.begin();
        if (lastSlash_i != std::string::npos)
        {
            nameStart += lastSlash_i + 1;
        }

        size_t lastPeriod_i = m_buffer.find_last_of('.');
        std::string::iterator nameEnd = m_buffer.end();
        if (lastPeriod_i != std::string::npos)
        {
            nameEnd = m_buffer.begin() + lastPeriod_i;
        }

        m_buffer.replace(nameStart, nameEnd, fileName);
    }

    void Path::setFileExtension(const std::string& extension)
    {
        if (m_buffer.empty()) return;

        size_t lastPeriod_i = m_buffer.find_last_of('.');
        std::string::iterator extensionStart = m_buffer.end();
        if (lastPeriod_i != std::string::npos)
        {
            extensionStart = m_buffer.begin() + lastPeriod_i + 1;
        }
        else
        {
            m_buffer += '.';
            extensionStart++;
        }

        m_buffer.replace(extensionStart, m_buffer.end(), extension);
    }

    bool Path::empty() const
    {
        return m_buffer.empty();
    }

    int Path::segments() const
    {
        int segments = 1;

        for (int i = 0; i < m_buffer.length() - 1; i++)
        {
            if (m_buffer[i] == '\\' && m_buffer[i + 1] != '\\') segments++;
        }

        return segments;
    }

    std::optional<std::string_view> Path::directory() const
    {
        size_t directoryEnd = m_buffer.find_last_of('\\');

        if (directoryEnd != std::string_view::npos)
        {
            return m_buffer.substr(0, directoryEnd);
        }
        else
        {
            return std::nullopt;
        }
    }

    std::optional<std::string_view> Path::parent() const
    {
        size_t parentEnd = m_buffer.find_last_of('\\');

        if (parentEnd == std::string_view::npos)
        {
            return std::nullopt;
        }

        size_t parentStart = m_buffer.find_last_of('\\', parentEnd - 1);

        if (parentStart == std::string_view::npos)
        {
            return m_buffer.substr(0, parentEnd);
        }

        size_t parentLength = parentEnd - parentStart - 1;

        return m_buffer.substr(parentStart + 1, parentLength);
    }

    std::string_view Path::fileName() const
    {
        size_t fileStart = m_buffer.find_last_of('\\');

        return m_buffer.substr(fileStart + 1);
    }

    std::string_view Path::fileRoot() const
    {
        size_t rootStart = m_buffer.find_last_of('\\');
        size_t rootEnd = m_buffer.find_last_of('.');
        size_t rootLength = rootEnd - rootStart - 1;

        return m_buffer.substr(rootStart + 1, rootLength);
    }

    std::optional<std::string_view> Path::fileExtension() const
    {
        size_t extensionStart = m_buffer.find_last_of('.');

        if (extensionStart != std::string_view::npos)
        {
            return m_buffer.substr(extensionStart + 1);
        }
        else
        {
            return std::nullopt;
        }
    }

    std::string Path::normalize(const std::string& path) const
    {
        std::string normalized = path;

        for (int i = 0; i < normalized.length(); i++)
        {
            if (normalized.substr(i, 2) == "//" || normalized.substr(i, 2) == "\\\\")
            {
                normalized.erase(i, 1);
                i--;
            }
            else if (normalized[i] == '/')
            {
                normalized[i] = '\\';
            }
        }

        return normalized;
    }
}