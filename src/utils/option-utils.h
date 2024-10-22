// Custom implementation of getopt

#ifndef OPTION_UTILS_H
#define OPTION_UTILS_H

#ifdef __cplusplus
extern "C" {
#endif 
	extern char* optionArgument;
	extern int argIndex, optionError;
	char optionFlag;

	char getNextFlag(int argc, char* const argv[], const char* allOptionsString);
#ifdef __cplusplus
}
#endif 

#endif // !OPTION_UTILS_H