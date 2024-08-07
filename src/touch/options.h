#ifndef TOUCH_OPTIONS_H
#define TOUCH_OPTIONS_H

#define MESSAGE_USAGE "Usage: touch [OPTION]... <FILE>...\n"
#define MESSAGE_HELP "TODO"

#define OPTION_FLAGS "hamdrc"

struct FLAGS_T {
    bool a; // change access time only
    bool m; // change modify time only
    bool d; // TODO - set access and modify time from string
    bool r; // TODO - set access and modify time from another file's
    bool c; // TODO - supress file creation if doesnt exist
    bool t; // TODO - create file using specified YYMMDDHHMM
} FLAGS_DEFAULT = {
    false,
    false,
    false,
    false,
    false,
    false
};
typedef struct FLAGS_T FLAGS;

#endif // !TOUCH_OPTIONS_H
