// Utility for grep.c
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

// Passed options
struct GrepOpts_s {
    bool c; // count lines
    bool i; // ignore case
    bool l; // only file name
    bool n; // show line number
    bool v; // only lines that didnt match
    bool w; // search for whole word
    bool o; // only matching parts
    char *e; // regex
    char *f; // pattern from file
} GrepOpts_default = {
    false,
    false,
    false,
    false,
    false,
    false,
    false
};
typedef struct GrepOpts_s GrepOpts, *PGrepOpts;

// Functions

/*
    Opens and reads directory from path
*/
void readDir(const char *path, char *pattern, GrepOpts *opts);

/*
    Opens and reads file from path
*/
void readFile(const char *path, char *pattern, GrepOpts *opts);

// Strings

#define MSG_USAGE "Usage: grep [OPTIONS] <PATTERN> <PATH>\n"
#define GREP_OPTIONS "hcilnvwoe: f: "

#endif