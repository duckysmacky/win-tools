#ifndef TOUCH_H
#define TOUCH_H

// Includes

#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <getopt.h>
#include <sys/stat.h>
#include <windows.h>

#include "../../include/arr-utils.h"
#include "../../include/str-utils.h"

// Data

#define true 1
#define false 0
#define bool unsigned char

// Options
struct Opts_t {
    bool a; // change access time only
    bool m; // change modify time only
    bool d; // TODO - set access and modify time from string
    bool r; // TODO - set access and modify time from another file's
    bool c; // TODO - supress file creation if doesnt exist
    bool t; // TODO - create file using specified YYMMDDHHMM
} Opts_default = {
    false,
    false,
    false,
    false,
    false,
    false
};
typedef struct Opts_t Opts, *POpts;

// Strings

#define MSG_USAGE "Usage: touch [OPTIONS] <PATH>\n"
#define OPTION_FLAGS "hamdrc"

// Functions

void updateFile(char *fpath, Opts *opts);

void createFile(char *path);

#endif // TOUCH_H