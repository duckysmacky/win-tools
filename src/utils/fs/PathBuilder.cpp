#include "PathBuilder.h"

#include <string>
#include <vector>
#include <format>

#include "Path.h";

namespace utils::fs
{
    // Public

    PathBuilder::PathBuilder()
        : m_hasFile(false)
    {
        m_pathBuffer.push_back(".");
    }

    PathBuilder::PathBuilder(const std::string& path)
        : m_hasFile(false)
    {
        m_pathBuffer.push_back(".");
        append(path);
    }

    void PathBuilder::append(const std::string& path)
    {
        std::string pathSegment = "";

        for (int i = 0; i < path.length(); i++)
        {
            if (path[i] == '/' || path[i] == '\\')
            {
                m_pathBuffer.push_back(pathSegment);
                pathSegment.clear();
                continue;
            }

            pathSegment += path[i];
        }

        m_pathBuffer.push_back(pathSegment);
    }

    std::string PathBuilder::pop()
    {
        std::string last;
        if (m_hasFile)
        {
            last = fileName();
            m_fileRoot.clear();
            m_fileExtention.clear();
            m_hasFile = false;
        }
        else
        {
            last = m_pathBuffer.back();
            m_pathBuffer.pop_back();
        }
        return last;
    }

    void PathBuilder::clear()
    {
        if (m_hasFile)
        {
            m_fileRoot.clear();
            m_fileExtention.clear();
            m_hasFile = false;
        }
        m_pathBuffer.clear();
    }

    void PathBuilder::setFileName(const std::string& fileName)
    {
        m_fileRoot = fileName;
    }

    void PathBuilder::setFileExtention(const std::string& fileExtention)
    {
        m_fileExtention = fileExtention;
    }

    Path* PathBuilder::build() const
    {
        return nullptr;
    }

    Path* PathBuilder::with(const std::string& path) const
    {
        return nullptr;
    }

    int PathBuilder::elements() const
    {
        int elements = m_pathBuffer.size();
        if (m_hasFile) elements += 1;
        return elements;
    }

    std::string PathBuilder::str() const
    {
        std::string str = buildPathBuffer();
        if (hasFile)
            str += fileName();
        return std::string();
    }

    std::string PathBuilder::tail() const
    {
        std::string tail;
        if (m_hasFile)
        {
            tail = fileName();
        }
        else
        {
            tail = m_pathBuffer.back();
        }
        return tail;
    }

    std::string PathBuilder::fileName() const
    {
        std::string fileName;
        if (hasFile)
        {
            fileName += m_fileRoot;
            if (!m_fileExtention.empty())
                fileName += "." + m_fileExtention;
        }
        return fileName;
    }

    std::string PathBuilder::fileRoot() const
    {
        return m_fileRoot;
    }

    std::string PathBuilder::fileExtention() const
    {
        return m_fileExtention;
    }

    bool PathBuilder::hasFile() const
    {
        return m_hasFile;
    }

    // Private

    std::string PathBuilder::buildPathBuffer() const
    {
        std::string path;

        for (std::string segment : m_pathBuffer)
        {
            path += segment + SLASH;
        }

        return path;
    }
}