#ifndef GREP_OPTIONS_H
#define GREP_OPTIONS_H

#include <stdbool.h>

#define MESSAGE_USAGE "Usage: grep [OPTION]... <PATTERN> [FILE]\nDo \"grep -h\" for help\n"
#define MESSAGE_HELP "TODO"

#define OPTION_FLAGS "hcilnvwoe: f: "

struct FLAGS_T {
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
} FLAGS_DEFAULT = {
    false,
    false,
    false,
    false,
    false,
    false,
    false,
    false
};
typedef struct FLAGS_T FLAGS;

#endif // !GREP_OPTIONS_H
