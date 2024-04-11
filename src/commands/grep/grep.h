// Utility for grep.c
#ifndef GREP_H
#define GREP_H

// Includes

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <unistd.h>

#include "../../headers/arr-utils.h"
#include "../../headers/str-utils.h"
#include "../../headers/colors.h"

// Data

// Passed options
typedef struct GrepOpts {
    bool c; // count lines
    bool i; // ignore case
    bool l; // only file name
    bool n; // show line number
    bool v; // only lines that didnt match
    bool w; // search for whole word
    bool o; // only matching parts
    char *e; // regex
    char *f; // pattern from file
} GrepOpts, *PGrepOpts;

// Bool datatype
typedef unsigned char bool;
#define true 1
#define false 0

// Functions

/*
    Opens and reads directory from path
*/
void readDir(const char *path, const char *pattern, GrepOpts opts);

/*
    Opens and reads file from path
*/
void readFile(const char *path, const char *pattern, GrepOpts opts);

// Strings

#define MSG_USAGE "Usage: grep [OPTIONS] <PATTERN> <PATH>\n"
#define GREP_OPTIONS "hcilnvefwo"

#endif