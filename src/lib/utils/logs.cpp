#include "./logs.h"

#include <iostream>

namespace utils
{
	void logError(const std::string& message)
	{
		std::cerr << "Error: " << message << std::endl;
	}

	void logError(const std::string& message, int code)
	{
		std::cerr << "Error: " << message << " (" << code << ")" << std::endl;
	}
}