#include "PathBuilder.h"

// Private

void utils::files::PathBuilder::appendPathSegments(const std::string& path)
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

void utils::files::PathBuilder::appendPathSegments(std::vector<std::string>& targetPathBuffer, const std::string& path) const
{
    std::string pathSegment = "";

    for (int i = 0; i < path.length(); i++)
    {
        if (path[i] == '/' || path[i] == '\\')
        {
            targetPathBuffer.push_back(pathSegment);
            pathSegment.clear();
            continue;
        }

        pathSegment += path[i];
    }

    targetPathBuffer.push_back(pathSegment);
}

std::string utils::files::PathBuilder::buildPathBuffer() const
{
    std::string path;

    for (std::string segment : m_pathBuffer)
    {
        path += segment + "/";
    }

    return path;
}

std::string utils::files::PathBuilder::buildPathBuffer(const std::vector<std::string> pathBuffer) const
{
    std::string path;

    for (std::string segment : pathBuffer)
    {
        path += segment + "/";
    }

    return path;
}

// Public

utils::files::PathBuilder::PathBuilder()
{
	m_pathBuffer.push_back(".");
}

utils::files::PathBuilder::PathBuilder(const std::string& path)
{
	m_pathBuffer.push_back(".");
	appendPathSegments(path);
}

void utils::files::PathBuilder::operator<<(const std::string& path)
{
    appendPathSegments(path);
}

void utils::files::PathBuilder::append(const std::string& path)
{
    appendPathSegments(path);
}

std::string utils::files::PathBuilder::join(const std::string& path) const
{
    auto prefixPathBuffer = std::vector<std::string>(m_pathBuffer.begin(), m_pathBuffer.end() - 1);
    appendPathSegments(prefixPathBuffer, path);
    return buildPathBuffer(prefixPathBuffer);
}

std::string utils::files::PathBuilder::getPath() const
{
    return buildPathBuffer();
}

std::string utils::files::PathBuilder::getLast() const
{
    return m_pathBuffer.back();
}
