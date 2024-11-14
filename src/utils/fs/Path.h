#ifndef UTILS_PATH_H
#define UTILS_PATH_H

#include <string>

namespace utils::fs
{
	class Path
	{
	public:
		Path(const std::string& path);
		Path(const std::string& dirPath, const std::string& fileRoot, const std::string fileExtention);
		~Path() = default;

		PathBuilder asBuilder() const;

		bool exists() const;
		bool isFile() const;
		bool isDirectory() const;
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
		int m_elements;
		bool m_isFile;
	};
}

#endif // !UTILS_PATH_H