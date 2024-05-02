#ifndef GREP_H
#define GREP_H

// Includes

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <unistd.h>

#include "../../include/arr-utils.h"
#include "../../include/str-utils.h"
#include "../../include/colors.h"

// Data

#define true 1
#define false 0
#define bool unsigned char

// Options struct
struct Opts_t {
    bool c; // count lines
    bool i; // ignore case
    bool l; // only file name
    bool n; // show line number
    bool v; // only lines that didnt match
    bool w; // TODO match whole word only
    bool o; // TODO only matching parts
    char *e; // TODO regex
    char *f; // pattern from file
} Opts_default = {
    false,
    false,
    false,
    false,
    false,
    false,
    false
};
typedef struct Opts_t Opts, *POpts;

// Functions

/*
    Opens and reads directory from path
*/
void readDir(const char *path, char *pattern, Opts *opts);

/*
    Opens and reads file from path
*/
void readFile(const char *path, char *pattern, Opts *opts);

// Strings

#define MSG_USAGE "Usage: grep [OPTIONS] <PATTERN> <PATH>\n"
#define OPTION_FLAGS "hcilnvwoe: f: "

#endif