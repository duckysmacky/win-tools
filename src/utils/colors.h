#ifndef COLORS_H
#define COLORS_H

// Color values
#define COLOR_RESET "\033[0m"
#define COLOR_BLACK "\033[0;30m"
#define COLOR_RED "\033[0;31m"
#define COLOR_GREEN "\033[0;32m"
#define COLOR_YELLOW "\033[0;33m"
#define COLOR_BLUE "\033[0;34m"
#define COLOR_PURPLE "\033[0;35m"
#define COLOR_CYAN "\033[0;36m"
#define COLOR_WHITE "\033[0;37m"

// Print color macros
#define printBlack(msg, ...) printf("%s" msg "%s", COLOR_BLACK, ##__VA_ARGS__, COLOR_RESET);
#define printRed(msg, ...) printf("%s" msg "%s", COLOR_RED, ##__VA_ARGS__, COLOR_RESET);
#define printGreen(msg, ...) printf("%s" msg "%s", COLOR_GREEN, ##__VA_ARGS__, COLOR_RESET);
#define printYellow(msg, ...) printf("%s" msg "%s", COLOR_YELLOW, ##__VA_ARGS__, COLOR_RESET);
#define printBlue(msg, ...) printf("%s" msg "%s", COLOR_BLUE, ##__VA_ARGS__, COLOR_RESET);
#define printPurple(msg, ...) printf("%s" msg "%s", COLOR_PURPLE, ##__VA_ARGS__, COLOR_RESET);
#define printCyan(msg, ...) printf("%s" msg "%s", COLOR_CYAN, ##__VA_ARGS__, COLOR_RESET);
#define printWhite(msg, ...) printf("%s" msg "%s", COLOR_WHITE, ##__VA_ARGS__, COLOR_RESET);

#endif