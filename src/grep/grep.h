#ifndef COMMANDS_GREP_H
#define COMMANDS_GREP_H

#include "framework.h"

#include <string>

#define NAME "Grep"
#define VERSION "1.0.0"

#define MESSAGE_VERSION NAME " v" VERSION
#define MESSAGE_USAGE "Usage: grep [OPTIONS]... <PATTERN> <FILE>...\nDo \"grep -h\" for help\n"
#define MESSAGE_HELP "TODO"

#define OPTION_FLAGS "Vhiwnclvf: "

struct Options
{
    bool ignoreCase; // i
    bool showLineNumber; // n
    bool onlyCountLines; // c
    bool onlyFileName; // l
    bool onlyUnmatched; // v
    bool recursive; // R
    std::string patternFilePath; // f

    Options()
    {
        ignoreCase = false;
        showLineNumber = false;
        onlyCountLines = false;
        onlyFileName = false;
        onlyUnmatched = false;
        recursive = false;
        patternFilePath = "";
    }
};

#endif //!COMMANDS_GREP_H