#ifndef OPTION_UTILS_H
#define OPTION_UTILS_H

// Custom implementation of getopt

extern char* optionArgument;
extern int optionIndex, optionError;
char optionFlag;

#ifdef __cplusplus
extern "C" {
#endif 
	char getNextFlag(int argc, char* const argv[], const char* allOptionsString);
#ifdef __cplusplus
}
#endif 

#endif // !OPTION_UTILS_H