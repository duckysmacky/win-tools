#ifndef TOUCH_H
#define TOUCH_H

// Includes
#include <sys/stat.h>

#include "framework.h"
#include "array-utils.h"
#include "string-utils.h"
#include "option-utils.h"
#include "directory-utils.h"

#include "options.h"

// Functions

int updateFile(char *fpath, FLAGS *opts);
int createFile(char *path);

#endif // TOUCH_H