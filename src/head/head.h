#ifndef COMMANDS_HEAD_H
#define COMMANDS_HEAD_H

#include "framework.h"

#define VERSION "1.0.1"

#define MESSAGE_VERSION "Grep (v" VERSION ") - developed by github.com/duckysmacky"
#define MESSAGE_USAGE "Usage: head [OPTIONS]... <FILE>...\nDo \"head -h\" for help\n"
#define MESSAGE_HELP "TODO"

#define OPTIONS_FLAGS "Vhvqn: "

struct Options
{
    bool showFileName; // v
    bool hideFileName; // q
    int nLines; // n

    Options()
    {
        showFileName = false;
        hideFileName = false;
        nLines = 10;
    }
};

#endif // !COMMANDS_HEAD_H