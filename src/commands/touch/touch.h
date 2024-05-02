#ifndef TOUCH_H
#define TOUCH_H

// Includes

#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <getopt.h>
#include <sys/stat.h>

#include "../../include/arr-utils.h"
#include "../../include/str-utils.h"

// Data

#define true 1
#define false 0
#define bool unsigned char

// Options
struct Opts_t {
    bool a; // TODO - change access time only
    bool m; // TODO - change modift time only
    bool d; // TODO - set access and modify time from string
    bool r; // TODO - set access and modify time from file
    bool c; // TODO - supress file creation if doesnt exist
} Opts_default = {
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

#endif // TOUCH_H