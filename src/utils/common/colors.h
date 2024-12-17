#ifndef UTILS_COLORS_H
#define UTILS_COLORS_H

#include <iostream>

// Color values
#define COLOR_RESET "\033[0m"
#define COLOR_BLACK "\033[0;30m"
#define COLOR_RED "\033[0;31m"
#define COLOR_GREEN "\033[0;32m"
#define COLOR_YELLOW "\033[0;33m"
#define COLOR_BLUE "\033[0;34m"
#define COLOR_PURPLE "\033[0;35m"
#define COLOR_CYAN "\033[0;36m"
#define COLOR_WHITE "\033[0;37m"

namespace colors
{
	constexpr auto RESET = COLOR_RESET;
	constexpr auto BLACK = COLOR_BLACK;
	constexpr auto RED = COLOR_RED;
	constexpr auto GREEN = COLOR_GREEN;
	constexpr auto YELLOW = COLOR_YELLOW;
	constexpr auto BLUE = COLOR_BLUE;
	constexpr auto PURPLE = COLOR_PURPLE;
	constexpr auto CYAN = COLOR_CYAN;
	constexpr auto WHITE = COLOR_WHITE;
}

namespace utils
{
	// Colored std::cout alternative
	class ccout
	{
	public:
		inline ccout(const std::string& color);
		inline ~ccout();
	
	    template <class T>
		inline ccout& operator<<(const T& input);
	};
}

#endif // !UTILS_COLORS_H