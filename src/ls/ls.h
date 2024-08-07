#ifndef LS_H
#define LS_H

// Includes
#include <time.h>

#include "framework.h"
#include "colors.h"
#include "array-utils.h"
#include "directory-utils.h"
#include "option-utils.h"

#include "options.h"

// Functions

LONGLONG getDirSize(char *fpath);

/*
    List items in dir
*/
void listDir(const char *path, FLAGS *opts);

/*
    Read dir and find subdirs, then list them if found
*/
void readDir(const char *path, FLAGS *opts);

/*
    Generates a long info format for file
*/
char* formatLongFile(char *fpath, char *fname);

#endif // LS_H