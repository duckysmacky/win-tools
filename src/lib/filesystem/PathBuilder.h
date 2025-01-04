#ifndef FILESYSTEM_PATH_BUILDER_H
#define FILESYSTEM_PATH_BUILDER_H

#include <string>
#include <vector>

#include "Path.h"

#define SLASH "/"

namespace fs
{
	// A helper class for easier work with paths
	class PathBuilder
	{
	public:
		PathBuilder();
		PathBuilder(const std::string& path);
		~PathBuilder() = default;

		void append(const std::string& path);
		std::string pop();
		void clear();

		void setFileName(const std::string& fileName);
		void setFileExtention(const std::string& fileExtention);

		Path* build() const;
		Path* with(const std::string& path) const;

		int elements() const;
		std::string str() const;
		std::string tail() const;
		std::string fileName() const;
		std::string fileRoot() const;
		std::string fileExtention() const;
		bool hasFile() const;
		
	private:
		std::vector<std::string> m_pathBuffer;
		std::string m_fileRoot;
		std::string m_fileExtention;
		bool m_hasFile;

		// Build buffer by connecting segments with slashes
		std::string buildPathBuffer() const;
	};
}

#endif // !FILESYSTEM_PATH_BUILDER_H