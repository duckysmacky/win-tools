#ifndef COMMANDS_LS_H
#define COMMANDS_LS_H

#define NAME "Ls"
#define VERSION "1.0.0"

// Settings

#include "utils.h" // colors

// I don't even remember how, why or what for. No questions here
#define MAGIC_WIDTH 11

#define LIST_NAME_EXEPTIONS { "Makefile" }

#define COLOR_FILE_DIRECTORY COLOR_BLUE
#define COLOR_FILE_HIDDEN COLOR_CYAN
#define COLOR_FILE_EXECUTABLE COLOR_YELLOW
#define COLOR_FILE_OTHER COLOR_GREEN

#endif // !COMMANDS_LS_H