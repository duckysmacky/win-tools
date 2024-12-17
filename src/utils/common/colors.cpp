#include "./colors.h"

#include <iostream>

namespace utils
{
	inline ccout::ccout(const std::string& color)
	{
		std::cout << color;
	}

	inline ccout::~ccout()
	{
		std::cout << colors::RESET << std::endl;
	}

	template <class T>
	inline ccout& ccout::operator <<(const T& input)
	{
		std::cout << input;
		return *this;
	}
}
