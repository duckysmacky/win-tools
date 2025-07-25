#pragma once

#include "utils/general.h"

constexpr auto NAME = "ls";
constexpr auto VERSION = "1.0.0";

// I don't even remember how, why or what for. No questions here
constexpr auto MAGIC_WIDTH = 11;

#define LIST_NAME_EXEPTIONS { "Makefile" }

#define COLOR_FILE_DIRECTORY COLOR_BLUE
#define COLOR_FILE_HIDDEN COLOR_CYAN
#define COLOR_FILE_EXECUTABLE COLOR_YELLOW
#define COLOR_FILE_OTHER COLOR_GREEN
