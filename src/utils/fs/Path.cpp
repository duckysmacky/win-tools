#include "Path.h"

#include <string>
#include <filesystem>

namespace utils::fs
{
	Path::Path(const std::string& path)
	{
		parsePath(path);
	}

	bool Path::isFile() const
	{
		return m_isFile;
	}

	bool Path::isDirectory() const
	{
		return !m_isFile;
	}

	std::string Path::with(const std::string& path) const
	{
		return std::string();
	}

	std::string Path::str() const
	{
		std::string str = m_dirPath;
		if (m_isFile)
		{
			str += fileName();
		}
		return str;
	}

	std::string Path::directory() const
	{
		return m_dirPath;
	}

	std::string Path::tail() const
	{
		return std::string();
	}

	std::string Path::fileName() const
	{
		std::string fileName;
		if (m_isFile)
		{
			fileName += m_fileRoot;
			if (!m_fileExtention.empty()) fileName += m_fileExtention;
		}
		return fileName;
	}

	std::string Path::fileRoot() const
	{
		return m_fileRoot;
	}

	std::string Path::fileExtention() const
	{
		return m_fileExtention;
	}

	void Path::parsePath(const std::string& path)
	{
		// dir/dir/name.ex
		if (path.back() == '/' || path.back() == '\\')
		{
			m_dirPath = path;
			m_isFile = false;
			return;
		}

		size_t slashIndex = 0;
		if (path.rfind('/') != std::string::npos || path.rfind('\\') != std::string::npos)
		{
			size_t slashIndexRight = (path.rfind('/') != std::string::npos) ? path.rfind('/') : -1;
			size_t slashIndexLeft = (path.rfind('\\') != std::string::npos) ? path.rfind('\\') : -1;
			slashIndex = std::max(slashIndexLeft, slashIndexRight);
		}
		else
		{
			m_dirPath = path;
			m_isFile = false;
			return;
		}

		std::string fileName(path.begin() + slashIndex + 1, path.end());
		if (fileName.empty())
		{
			m_dirPath = path;
			m_isFile = false;
			return;
		}

		size_t dotIndex = fileName.rfind('.');
		if (dotIndex == std::string::npos)
		{
			m_dirPath = path;
			m_isFile = false;
			return;
		}

		if (dotIndex == 0)
		{
			// Assuming that .file is a directory
			// TODO: add exclusions (e.g.: .gitignore)
			m_dirPath = path;
			m_isFile = false;
			return;
		}

		// dir/file.ex
		m_dirPath = std::string(path.begin(), path.begin() + slashIndex + 1);
		m_fileRoot = std::string(path.begin() + slashIndex + 1, path.begin() + dotIndex);
		m_fileExtention = std::string(path.begin() + dotIndex + 1, path.end());
		m_isFile = true;
	}
}