#ifndef HEAD_H
#define HEAD_H

// Includes

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>
#include <windows.h>

#include "../../include/arr-utils.h"
#include "../../include/str-utils.h"

// Data

#define true 1
#define false 0
#define bool unsigned char

// Options
#define OPTION_FLAGS "qvzn: c:"

struct Opts_t {
    bool q; // TODO don't print file names
    bool v; // TODO always print file names
    int n; // TODO number of lines to print
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