#ifndef COMMANDS_LS_H
#define COMMANDS_LS_H

#define NAME "Ls"
#define VERSION "1.0.0"

#define MESSAGE_VERSION NAME " v" VERSION
#define MESSAGE_USAGE "Usage: ls [OPTIONS]... <DIRECTORY>\n"
#define MESSAGE_HELP "TODO"

#define OPTION_FLAGS "hlatrigHdsAR123456789"

#include <stdbool.h>

struct FLAGS_T {
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
} FLAGS_DEFAULT = {
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
typedef struct FLAGS_T FLAGS;

#endif // !COMMANDS_LS_H