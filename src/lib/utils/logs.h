#ifndef UTILS_LOGS_H
#define UTILS_LOGS_H

#include <string>

namespace utils
{
	void logError(const std::string& message);
	void logError(const std::string& message, int code);
}

#endif // !UTILS_LOGS_H
