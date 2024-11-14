#ifndef UTILS_PATH_H
#define UTILS_PATH_H

#include <string>

namespace utils::fs
{
	class Path
	{
	public:
		Path(const std::string& path);
		~Path() = default;

		bool exists() const;
		bool isFile() const;
		bool isDirectory() const;
		bool isAbsolute() const;
		bool isRelative() const;

		std::string with(const std::string& path) const;

		std::string string() const;
		std::string parent() const;
		std::string	end() const;
		std::string fileName() const;
		std::string fileExtention() const;

	};
}

#endif // !UTILS_PATH_H