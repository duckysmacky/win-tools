#include "./Path.h"

#include <format>
#include <string>
#include <string_view>
#include <optional>

#include <Windows.h>

namespace fs
{
	Path::Path(const std::string& path)
		: m_path(path) {}

	Path::Path(std::string_view path)
		: m_path(path) {}

	Path::Path(const char* path)
		: m_path(path) {}

	Path::operator std::string_view() const
	{
		return m_path;
	}

	Path::operator std::string() const
	{
		return std::string(m_path);
	}

	bool Path::exists() const
	{
		DWORD fileAttributes = GetFileAttributesA(m_path.data());

		return fileAttributes != INVALID_FILE_ATTRIBUTES;
	}

	bool Path::isDirectory() const
	{
		DWORD fileAttributes = GetFileAttributesA(m_path.data());

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
		DWORD fileAttributes = GetFileAttributesA(m_path.data());

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
		DWORD fileAttributes = GetFileAttributesA(m_path.data());

		if (fileAttributes != INVALID_FILE_ATTRIBUTES)
		{
			return fileAttributes & FILE_ATTRIBUTE_HIDDEN;
		}
		else
		{
			return fileRoot().at(0) == '.';
		}
	}

	Path Path::with(std::string_view subpath) const
	{
		return Path(std::string(m_path).append(subpath));
	}

	std::string Path::toString() const
	{
		return std::string(m_path);
	}

	std::optional<std::string_view> Path::directory() const
	{
		size_t directoryEnd = m_path.find_last_of('\\');

		if (directoryEnd != std::string_view::npos)
		{
			return m_path.substr(0, directoryEnd);
		}
		else
		{
			return std::nullopt;
		}
	}

	std::optional<std::string_view> Path::parent() const
	{
		size_t parentEnd = m_path.find_last_of('\\');

		if (parentEnd == std::string_view::npos)
		{
			return std::nullopt;
		}

		size_t parentStart = m_path.find_last_of('\\', parentEnd - 1);

		if (parentStart == std::string_view::npos)
		{
			return m_path.substr(0, parentEnd);
		}

		size_t parentLength = parentEnd - parentStart - 1;

		return m_path.substr(parentStart + 1, parentLength);
	}

	std::string_view Path::fileName() const
	{
		size_t fileStart = m_path.find_last_of('\\');

		return m_path.substr(fileStart + 1);
	}

	std::string_view Path::fileRoot() const
	{
		size_t rootStart = m_path.find_last_of('\\');
		size_t rootEnd = m_path.find_last_of('.');
		size_t rootLength = rootEnd - rootStart - 1;

		return m_path.substr(rootStart + 1, rootLength);
	}

	std::optional<std::string_view> Path::fileExtension() const
	{
		size_t extensionStart = m_path.find_last_of('.');

		if (extensionStart != std::string_view::npos)
		{
			return m_path.substr(extensionStart + 1);
		}
		else
		{
			return std::nullopt;
		}
	}
}