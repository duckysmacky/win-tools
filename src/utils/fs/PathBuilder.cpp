#include "PathBuilder.h"

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

    // Private

    std::string PathBuilder::buildPathBuffer() const
    {
        std::string path;

        for (std::string segment : m_pathBuffer)
        {
            path += segment + "/";
        }

        return path;
    }
}