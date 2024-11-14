#ifndef UTILS_PATH_BUILDER_H
#define UTILS_PATH_BUILDER_H

#include <string>
#include <vector>

#include "Path.h"

namespace utils::fs
{
	// A helper class for easier work with paths
	class PathBuilder
	{
	public:
		PathBuilder();
		PathBuilder(const std::string& path);
		~PathBuilder() = default;

		void append(const std::string& path);
		void pop();
		void clear();

		void setFileName(const std::string& fileName);
		void setFileExtention(const std::string& fileExtention);

		Path* build() const;
		Path* with(const std::string& path) const;

		std::string string() const;
		std::string end() const;
		std::string file() const;
		std::string fileName() const;
		std::string fileExtention() const;
		int parts() const; // TODO: rename function
		
		std::string hasFile() const;

	private:
		std::vector<std::string> m_pathBuffer;
		bool m_hasFile;

		// Build buffer by connecting segments with slashes
		std::string buildPathBuffer() const;
	};
}

#endif // !UTILS_PATH_BUILDER_H