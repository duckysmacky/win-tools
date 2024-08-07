#ifndef HEAD_H
#define HEAD_H

// Includes

#include "framework.h"
#include "array-utils.h"
#include "string-utils.h"
// Options
#define OPTION_FLAGS "qvzn: c:"

struct Opts_t {
    bool v; // always print file names
    bool q; // don't print file names
    int n; // number of lines to print
    int c; // TODO number of bytes to print
} Opts_default = {
    false,
    false,
    0,
    0
};

typedef struct Opts_t Opts, *POpts;

// Strings

#define MSG_USAGE "Usage: head [OPTIONS] <FILE_NAME>...\n"
#define MSG_HELP "Do \"head -h\" for help\n"

// Functions

void readFile(char *path, Opts *opts);

#endif // LS_H