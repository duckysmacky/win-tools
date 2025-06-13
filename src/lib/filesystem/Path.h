#ifndef FILESYSTEM_PATH_H
#define FILESYSTEM_PATH_H

namespace fs
{
	// An immutable view on a filesystem path
	class Path
	{
	private:
		std::string_view m_path;

	public:
		//* Constructors
		Path(const std::string& path);
		Path(std::string_view path);
		Path(const char* path);

		//* Destructors
		~Path() = default;

		//* Conversions
		operator std::string_view() const;
		operator std::string() const;

		//* Filesystem checks
		bool exists() const;
		bool isDirectory() const;
		bool isFile() const;
		bool isHidden() const;

		//* Path manipulation
		// Returns a new Path with a subpath appended at the end
		Path with(std::string_view subpath) const;

		//* Getters
		// Returns a full path as a string
		std::string toString() const;
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
		void normalizeSlashes(std::string_view& path);
	};
}

#endif // !FILESYSTEM_PATH_H