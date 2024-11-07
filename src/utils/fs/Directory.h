#ifndef UTILS_DIRECTORY_H
#define UTILS_DIRECTORY_H

#include <string>
#include <vector>

#include <Windows.h>

namespace utils::fs
{
	struct Entry
	{
		std::string name;
		std::string alternateName;
	};

	class Directory
	{
	private:
		HANDLE handle;
		LPWIN32_FIND_DATAA findData;
	
	public:
		Directory(const std::string& path);
		~Directory();
		std::vector<Entry> getEntries() const;
	};
}


#endif // !UTILS_DIRECTORY_H