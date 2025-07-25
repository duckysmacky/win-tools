#pragma once

#include "utils/colors.h"

constexpr auto NAME = "ls";
constexpr auto VERSION = "1.0.0";

// I don't even remember how, why or what for. No questions here
constexpr auto MAGIC_WIDTH = 11;

#define LIST_NAME_EXEPTIONS { "Makefile" }

#define COLOR_FILE_DIRECTORY colors::ansi::BLUE
#define COLOR_FILE_HIDDEN colors::ansi::CYAN
#define COLOR_FILE_EXECUTABLE colors::ansi::YELLOW
#define COLOR_FILE_OTHER colors::ansi::GREEN
