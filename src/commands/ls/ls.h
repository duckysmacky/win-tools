#ifndef LS_H
#define LS_H

// Includes

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <unistd.h>
#include <time.h>
#include <windows.h>

#include "../../include/arr-utils.h"
#include "../../include/colors.h"

// Data

#define true 1
#define false 0
#define bool unsigned char

// Ls Options
struct LsOpts {
    bool l; // TODO show detailed info about files and dirs
    bool a; // show all files (including hidden)
    bool t; // TODO sort by modify time
    bool r; // TODO reverse sort
    bool i; // TODO show index of files
    bool g; // TODO show group ownership (?)
    bool h; // TODO print file sizes in human-readable format (e.g. k, mb, gb)
    bool d; // list dirs instead of files
    bool s; // TODO sort by size
    bool A; // show ALL files (including hidden, . and ..)
    bool R; // show recursively (all subdirs)
    bool ol; // show in one line vertically
    // TODO - make "-1" better and scalable
} LsOpts_default = {
    false,
    false,
    false,
    false,
    false,
    false,
    false,
    false,
    false,
    false,
    false,
    false
};
typedef struct LsOpts Opts, *POpts;

// Strings

#define MSG_USAGE "Usage: ls [OPTIONS]\n"
#define OPTION_FLAGS "latrighdsAR1"

// Functions

/*
    List items in dir
*/
void listDir(const char *path, Opts *opts);

/*
    Read dir and find subdirs, then list them if found
*/
void readDir(const char *path, Opts *opts);

/*
    Generates a long info format for file
*/
char* formatLongFile(char *fpath, char *fname);

#endif // LS_H