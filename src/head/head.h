#ifndef COMMANDS_HEAD_H
#define COMMANDS_HEAD_H

#include "framework.h"

#define VERSION "1.0"

#define MESSAGE_USAGE "Usage: head [OPTIONS]... <FILE>...\nDo \"head -h\" for help\n"
#define MESSAGE_HELP "TODO"
#define OPTIONS_FLAGS "vqn: b:"

struct Options
{
    bool showFileName; // v
    bool hideFileName; // q
    int nLines; // n
    int nBytes; // b

    Options()
    {
        showFileName = false;
        hideFileName = false;
        nLines = 10;
        nBytes = 0;
    }
};

#endif // !COMMANDS_HEAD_H