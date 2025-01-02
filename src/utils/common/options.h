// DEPRICATED

#ifndef UTILS_COMMON_OPTIONS_H
#define UTILS_COMMON_OPTIONS_H
// Custom implementation of getopt

#ifdef __cplusplus
extern "C" {
#endif 
	extern char* optionArgument;
	extern int argIndex, optionError;
	extern char optionFlag;

	char getNextFlag(int argc, const char* argv[], const char* allOptionsString);
#ifdef __cplusplus
}
#endif 

#endif // !UTILS_COMMON_OPTIONS_H