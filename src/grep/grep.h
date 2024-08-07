#ifndef GREP_H
#define GREP_H

// Includes
#include "framework.h"
#include "colors.h"
#include "array-utils.h"
#include "string-utils.h"
#include "directory-utils.h"
#include "option-utils.h"

#include "options.h"

/*
    Opens and reads directory from path
*/
void readDir(const char *path, char *pattern, FLAGS *opts);

/*
    Opens and reads file from path
*/
void readFile(const char *path, char *pattern, FLAGS *opts);

#endif