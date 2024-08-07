#ifndef LS_H
#define LS_H

// Includes
#include <time.h>

#include "framework.h"
#include "colors.h"
#include "array-utils.h"
#include "directory-utils.h"

// Options
struct Opts_t {
    bool l; // show detailed info about files and dirs
    bool a; // show all files (including hidden)
    bool A; // show ALL files (including hidden, . and ..)
    bool t; // TODO sort by modify time
    bool r; // TODO reverse sort
    bool i; // TODO show index of files
    bool g; // TODO show group ownership (?)
    bool H; // TODO print file sizes in human-readable format (e.g. k, mb, gb)
    bool d; // list dirs instead of files
    bool s; // TODO sort by size
    bool R; // show recursively (all subdirs)
    int rows; // show in x rows vertically
} Opts_default = {
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
    0
};
typedef struct Opts_t Opts, *POpts;

// Strings

#define MSG_USAGE "Usage: ls [OPTIONS] [DIRECTORY]\n"
#define OPTION_FLAGS "hlatrigHdsAR123456789"

// Functions

LONGLONG getDirSize(char *fpath);

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