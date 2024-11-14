#ifndef UTILS_DIRECTORY_H
#define UTILS_DIRECTORY_H

#include <string>
#include <vector>

#include <Windows.h>
#include <stdint.h>

namespace utils::fs
{
	class Directory
	{
	public:
		struct Entry
		{
			std::string name;
			std::string alternateName;
		};

	public:
		Directory(const std::string& path);
		~Directory();

		std::vector<Entry> entries() const;
		int64_t size() const;

	private:
		HANDLE m_handle;
		WIN32_FIND_DATAA m_findData;
		std::vector<Entry> m_entries;
		int64_t m_size;

		int64_t getDirSize(const std::string& path);
	};
}


#endif // !UTILS_DIRECTORY_H