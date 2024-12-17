#include "./terminal.h"

#include <Windows.h>

namespace utils
{
	int getTerminalWidth()
	{
		CONSOLE_SCREEN_BUFFER_INFO terminalInfo;
		GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &terminalInfo);
		int terminalWidth = terminalInfo.srWindow.Right - terminalInfo.srWindow.Left + 1;
		return terminalWidth;
	}
}