#pragma once

#include <string>
#include <iostream>
#include <format>

#include <Windows.h>

namespace colors
{
	// ANSI codes for colors and additional formatting
	namespace ansi {
		constexpr auto RESET      = "\033[0m";

		constexpr auto BLACK      = "\033[30m";
		constexpr auto RED        = "\033[31m";
		constexpr auto GREEN      = "\033[32m";
		constexpr auto YELLOW     = "\033[33m";
		constexpr auto BLUE       = "\033[34m";
		constexpr auto PURPLE     = "\033[35m";
		constexpr auto CYAN       = "\033[36m";
		constexpr auto WHITE      = "\033[37m";

		constexpr auto BOLD       = "\033[1m";
		constexpr auto UNDERLINE  = "\033[4m";
	}

	// Custom endl type which resets color and flushes the stream
	struct endl_t {};
	constexpr endl_t endl;

	// Custom coloret output stream that works above std::cout
	class coloredStream
	{
	private:
		const char* m_color;

	public:
		explicit coloredStream(const char* ansiColorCode)
			: m_color(ansiColorCode) {}

		// Passes value into std::cout with set color
		template<typename T>
		coloredStream& operator<<(const T& value)
		{
			std::cout << m_color << value;
			return *this;
		}

		// Support for the custom colors::endl (resets color and flushes stream)
		coloredStream& operator<<(endl_t _)
		{
			std::cout << ansi::RESET << std::endl;
			return *this;
		}

		// Support for the STL stream manipulators
		coloredStream& operator<<(std::ostream& (*streamManipulator)(std::ostream&))
		{
			streamManipulator(std::cout);
			return *this;
		}
	};

	// Static ANSI initializer, which enables ANSI codes for the current console
	class ANSIInitializer
	{
	private:
		HANDLE m_hConsole;
		DWORD m_dwConsoleMode;

	public:
		ANSIInitializer()
			: m_hConsole(GetStdHandle(STD_OUTPUT_HANDLE))
			, m_dwConsoleMode(0)
		{
			GetConsoleMode(m_hConsole, &m_dwConsoleMode);

			if (isConsoleApp() && !(m_dwConsoleMode & ENABLE_VIRTUAL_TERMINAL_PROCESSING))
			{
				m_dwConsoleMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
				SetConsoleMode(m_hConsole, m_dwConsoleMode);
			}
		}

	private:
		bool isConsoleApp() const
		{
			if (m_hConsole == INVALID_HANDLE_VALUE) return false;
			return GetFileType(m_hConsole) == FILE_TYPE_CHAR;
		}
	};

	// Factory function / shortcut for coloredOutput
	inline coloredStream cout(const char* ansiColorCode)
	{
		return coloredStream(ansiColorCode);
	}

	// Returns a formatted string, which is colored to the specified color
	template<typename T>
	inline std::string paint(const char* ansiColorCode, const T& value)
	{
		return std::format("{}{}{}", ansiColorCode, value, ansi::RESET);
	}
	
	// Automatically initialize ANSI support at runtime
	namespace
	{
		ANSIInitializer _initializer;
	}
}
