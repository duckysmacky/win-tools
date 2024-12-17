#ifndef UTILS_FS_DIRECTORY_H
#define UTILS_FS_DIRECTORY_H

#include <string>
#include <vector>

#include <Windows.h>
#include <stdint.h>

namespace fs
{
	class Directory
	{
	public:
		struct Entry
		{
			std::string name;
			int64_t size;
			bool isDir;
		};

	public:
		Directory(const std::string& path);
		~Directory();

		std::vector<Entry> entries() const;
		int64_t size() const;

	private:
		std::string m_path;
		HANDLE m_handle;
		WIN32_FIND_DATAA m_findData;
		std::vector<Entry> m_entries;

		int64_t getDirSize(const std::string& path) const;

	};
}

#endif // !UTILS_FS_DIRECTORY_H