#ifndef UTILS_FS_PATH_H
#define UTILS_FS_PATH_H

#include <string>

namespace fs
{
	class Path
	{
	public:
		Path(const std::string& fullPath);
		Path(const std::string& dirPath, const std::string& fileRoot);
		Path(const std::string& dirPath, const std::string& fileRoot, const std::string fileExtention);
		~Path() = default;

		bool exists() const;
		bool isDirectory() const;
		bool isFile() const;
		bool isHidden() const;
		bool isAbsolute() const;
		bool isRelative() const;

		std::string with(const std::string& path) const;

		std::string absolute() const;

		std::string str() const;
		std::string directory() const;
		std::string	tail() const;
		std::string fileName() const;
		std::string fileRoot() const;
		std::string fileExtention() const;

	private:
		std::string m_dirPath;
		std::string m_fileRoot;
		std::string m_fileExtention;
		bool m_exists;
		bool m_isDir;
		bool m_isFile;
		bool m_isHidden;

		void parsePath(const std::string& path);
		void parseFilePath(const std::string& path, size_t fileIndex);
	};
}

#endif // !UTILS_FS_PATH_H