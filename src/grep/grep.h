#ifndef GREP_H
#define GREP_H

// Includes
#include "framework.h"
#include "colors.h"
#include "array-utils.h"
#include "string-utils.h"
#include "directory-utils.h"

// Options struct
struct Opts_t {
    bool c; // count lines
    bool i; // ignore case
    bool l; // only file name
    bool n; // show line number
    bool v; // only lines that didnt match
    bool w; // TODO match whole word only
    bool o; // TODO only matching parts
    bool R; // TODO recursive search
    char *e; // TODO regex
    char *f; // pattern from file
} Opts_default = {
    false,
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

#define MSG_USAGE "Usage: grep [OPTIONS] <PATTERN> [FILE_NAME]...\n"
#define OPTION_FLAGS "hcilnvwoe: f: "

#endif