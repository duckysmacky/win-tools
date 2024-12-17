#include "./Path.h"

#include <string>
#include <format>

#include <Windows.h>

namespace fs
{
	Path::Path(const std::string& fullPath)
		: m_isDir(false), m_isFile(false), m_isHidden(false)
	{
		WIN32_FILE_ATTRIBUTE_DATA attributeData{};
		m_exists = GetFileAttributesExA(fullPath.c_str(), GetFileExInfoStandard, &attributeData) != 0;

		if (m_exists)
		{
			DWORD attributes = attributeData.dwFileAttributes;
			m_isDir = attributes & FILE_ATTRIBUTE_DIRECTORY;
			m_isFile = !m_isDir;
			m_isHidden = attributes & FILE_ATTRIBUTE_HIDDEN;
		}

		parsePath(fullPath);
	}

	Path::Path(const std::string& dirPath, const std::string& fileRoot)
		: m_dirPath(dirPath), m_fileRoot(fileRoot), m_isDir(false), m_isFile(true), m_isHidden(false)
	{
		WIN32_FILE_ATTRIBUTE_DATA attributeData{};
		std::string fullPath = std::format("{}{}", dirPath, fileRoot);
		m_exists = GetFileAttributesExA(fullPath.c_str(), GetFileExInfoStandard, &attributeData) != 0;

		if (m_exists)
		{
			DWORD attributes = attributeData.dwFileAttributes;
			m_isDir = attributes & FILE_ATTRIBUTE_DIRECTORY;
			m_isFile = !m_isDir;
			m_isHidden = attributes & FILE_ATTRIBUTE_HIDDEN;
		}
	}

	Path::Path(const std::string& dirPath, const std::string& fileRoot, const std::string fileExtention)
		: m_dirPath(dirPath), m_fileRoot(fileRoot), m_fileExtention(fileExtention), m_isDir(false), m_isFile(true), m_isHidden(false)
	{
		WIN32_FILE_ATTRIBUTE_DATA attributeData{};
		std::string fullPath = std::format("{}{}.{}", dirPath, fileRoot, fileExtention);
		m_exists = GetFileAttributesExA(fullPath.c_str(), GetFileExInfoStandard, &attributeData) != 0;

		if (m_exists)
		{
			DWORD attributes = attributeData.dwFileAttributes;
			m_isDir = attributes & FILE_ATTRIBUTE_DIRECTORY;
			m_isFile = !m_isDir;
			m_isHidden = attributes & FILE_ATTRIBUTE_HIDDEN;
		}
	}

	bool Path::isDirectory() const
	{
		return m_isDir;
	}

	bool Path::isFile() const
	{
		return m_isFile;
	}

	bool Path::isHidden() const
	{
		return m_isHidden;
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
		if (m_exists && m_isDir)
		{
			m_dirPath = path;
			return;
		}

		// if ends with a slash or is a dot (e.g. path/to/dir/ or .)
		if (path.back() == '/' || path.back() == '\\' || path == "." || path == "..")
		{
			m_dirPath = path;
			m_isDir = true;
			return;
		}
		
		// if we have atleast one slash, find the rightmost of the two variants (e.g. path/to/file.ext)
		if (path.rfind('/') != std::string::npos || path.rfind('\\') != std::string::npos)
		{
			size_t slashIndexRight = (path.rfind('/') != std::string::npos) ? path.rfind('/') : -1;
			size_t slashIndexLeft = (path.rfind('\\') != std::string::npos) ? path.rfind('\\') : -1;
			size_t slashIndex = max(slashIndexLeft, slashIndexRight);
			parseFilePath(path, slashIndex + 1);
		}
		else
		{
			parseFilePath(path, 0);
		}
	}

	void Path::parseFilePath(const std::string& path, size_t fileIndex)
	{
		std::string fileName(path.begin() + fileIndex, path.end());
		// if we end up with an empty name (just a safety check) (e.g. path/to/)
		if (fileName.empty())
		{
			m_dirPath = path;
			m_isDir = true;
			return;
		}

		size_t dotIndex = fileName.rfind('.');
		// in case there is no extention (e.g. path/to/dir) and we haven't checked existing before
		if (dotIndex == std::string::npos && !m_exists)
		{
			m_dirPath = path;
			m_isDir = true;
			return;
		}
		// or if it is a dotfile (e.g. path/to/.dotfile) and we haven't checked existing before
		// if haven't checked, assume that dotfile is a directory
		else if (dotIndex == 0 && !m_exists)
		{
			m_dirPath = path;
			m_isDir = true;
			m_isHidden = true;
			return;
		}

		// we passed all checks, it is fine to consider given path a path to a file (e.g. path/to/file.ext -> path/to/, file, ext)
		m_dirPath = std::string(path.begin(), path.begin() + fileIndex + 1);
		m_fileRoot = std::string(path.begin() + fileIndex + 1, path.begin() + dotIndex);
		m_fileExtention = std::string(path.begin() + dotIndex + 1, path.end());
	}
}