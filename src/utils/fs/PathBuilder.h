#ifndef UTILS_PATH_BUILDER_H
#define UTILS_PATH_BUILDER_H

#include <string>
#include <vector>

namespace utils::files
{
	// A helper class for easier work with paths
	class PathBuilder
	{
	private:
		// Holds the segments of the path
		std::vector<std::string> m_pathBuffer;

		// Split input path by segments and append to the buffer
		void appendPathSegments(const std::string& path);
		void appendPathSegments(std::vector<std::string>& targetPathBuffer, const std::string& path) const;
		// Build buffer by connecting segments with slashes
		std::string buildPathBuffer() const;
		std::string buildPathBuffer(const std::vector<std::string> pathBuffer) const;


	public:
		PathBuilder();
		PathBuilder(const std::string& path);
		~PathBuilder() = default;

		void operator <<(const std::string& path);

		// Adds the input path to the end of buffer
		void append(const std::string& path);
		// Sets the last buffer element to input path and
		// retuns the whole path without modifying the original
		std::string join(const std::string& path) const;

		// Returns the whole path
		std::string getPath() const;
		// Returns the last segment of the buffer
		std::string getLast() const;
	};
}

#endif // !UTILS_PATH_BUILDER_H