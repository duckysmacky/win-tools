#ifndef OPTION_UTILS_H
#define OPTION_UTILS_H

// Custom implementation of getopt

#include <stdio.h>
#include <string.h>

extern char* optionArgument;
extern int optionIndex, optionError;
char optionFlag;

char getNextFlag(int argc, char* const argv[], const char* allOptionsString);

#endif // !OPTION_UTILS_H