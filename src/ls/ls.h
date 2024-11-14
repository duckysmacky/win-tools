#ifndef COMMANDS_LS_H
#define COMMANDS_LS_H

#define NAME "Ls"
#define VERSION "1.0.0"

#define MESSAGE_VERSION NAME " v" VERSION
#define MESSAGE_USAGE "Usage: ls [OPTIONS]... <DIRECTORY>\n"
#define MESSAGE_HELP "TODO"

#include "colors.h"

#define OPTIONS_FLAGS "VhlaAdR123456789"

struct Options
{
    bool longFormat; // l
    bool showHidden; // a
    bool showAll; // A
    bool listDirs; // d
    bool recursive; // R
    int rows; // [1-9]
    // TODO bool showIndex; // i
    // TODO bool showGroup; // g
    // TODO bool humanSize; // H (e.g. k, mb, gb)
    // TODO bool sortByModifyTime; // t
    // TODO bool sortBySize; // s
    // TODO bool reverseSort; // r

    Options()
    {
        longFormat = false;
        showHidden = false;
        showAll = false;
        listDirs = false;
        recursive = false;
        rows = 0;
    }
};

// Settings

#define LIST_NAME_EXEPTIONS { "Makefile" }

#define FILE_COLOR_DIRECTORY COLOR_BLUE
#define FILE_COLOR_HIDDEN COLOR_CYAN
#define FILE_COLOR_EXECUTABLE COLOR_YELLOW
#define FILE_COLOR_OTHER COLOR_GREEN

#endif // !COMMANDS_LS_H