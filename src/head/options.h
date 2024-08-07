#ifndef HEAD_OPTIONS_H
#define HEAD_OPTIONS_H

#define MESSAGE_USAGE "Usage: head [OPTION]... <FILE>...\nDo \"head -h\" for help\n"
#define MESSAGE_HELP "TODO"

#define OPTION_FLAGS "qvzn: c:"

struct FLAGS_T {
    bool v; // always print file names
    bool q; // don't print file names
    int n; // number of lines to print
    int c; // TODO number of bytes to print
} FLAGS_DEFAULT = {
    false,
    false,
    0,
    0
};
typedef struct FLAGS_T FLAGS;

#endif // !HEAD_OPTIONS_H