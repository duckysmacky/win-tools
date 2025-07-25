#pragma once

#include <string>
#include <string_view>
#include <optional>

namespace fs
{
	// A class used to build and manipulate paths
	class Path
	{
	private:
		std::string m_buffer;

	public:
		Path(const std::string& path);
		Path(std::string_view path);
		Path(const std::string segments[]);

		~Path() = default;

		operator std::string() const;
		operator std::string_view() const;

		// Joins the subpath with current path and returns a new Path instance
		Path join(const std::string& subpath) const;
		// Append to the end of the path
		void push(const std::string& subpath);
		// Remove the end of the path and return it
		std::string pop();

		// Checks whether the file exists on the system
		bool exists() const;
		// Checks whether this is a path to a directory. If doesn't exist on the
		// disk, will try to check if the file doesn't have an extension
		bool isDirectory() const;
		// Checks whether this is a path to a file. If doesn't exist on the disk,
		// will try to check if the file has extension
		bool isFile() const;
		// Checks if the file is hidden. If doesn't exist on the disk, will try
		// to find a '.' at the start of the file name
		bool isHidden() const;

		// Set the full file name (last path segment)
		void setFile(const std::string& file);
		// Set the file name without changing the extension
		void setFileName(const std::string& fileName);
		// Set the file extension without change its name (after the last dot)
		void setFileExtension(const std::string& extension);

		// Returns wheather the Path Builder is empty
		bool empty() const;
		// Retuns the segment count in path
		int segments() const;
		// Returns only the directory part of the path
		std::optional<std::string_view> directory() const;
		// Returns the parent of the last segment
		std::optional<std::string_view> parent() const;
		// Returns the full file name (root + extension)
		std::string_view fileName() const;
		// Returns only the file root (no extension)
		std::string_view fileRoot() const;
		// Returns only the file extension (no root)
		std::optional<std::string_view> fileExtension() const;

	private:
		// Normalize given path. Replaces all '/' with '\', removes redundant
		// slashes
		std::string normalize(const std::string& path) const;
	};
}
