#ifndef TOUCH_H
#define TOUCH_H

// Includes
#include <sys/stat.h>

#include "framework.h"
#include "array-utils.h"
#include "string-utils.h"

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

#define MSG_USAGE "Usage: touch [OPTIONS] <FILE_NAME>...\n"
#define OPTION_FLAGS "hamdrc"

// Functions

void updateFile(char *fpath, Opts *opts);

void createFile(char *path);

#endif // TOUCH_H