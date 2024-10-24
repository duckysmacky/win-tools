#ifndef COMMANDS_TOUCH_H
#define COMMANDS_TOUCH_H

#include "framework.h"

#define NAME "Touch"
#define VERSION "1.0.0"

#define MESSAGE_VERSION NAME " v" VERSION
#define MESSAGE_USAGE "Usage: touch [OPTIONS]... <FILE>...\n"
#define MESSAGE_HELP "TODO"

#define OPTIONS_FLAGS "Vham"

struct Options
{
    bool accessTimeOnly; // a
    bool modifyTimeOnly; // m
    // TODO - set access and modify time from string d
    // TODO - set access and modify time from another file's r 
    // TODO - supress file creation if doesnt exist c
    // TODO - create file using specified YYMMDDHHMM t

    Options()
    {
        accessTimeOnly = false;
        modifyTimeOnly = false;
    }
};

#endif // !COMMANDS_TOUCH_H