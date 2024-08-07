#ifndef LS_OPTIONS_H
#define LS_OPTIONS_H

#define MESSAGE_USAGE "Usage: ls [OPTION]... [DIRECTORY]\n"
#define MESSAGE_HELP "TODO"

#define OPTION_FLAGS "hlatrigHdsAR123456789"

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

#endif // !LS_OPTIONS_H