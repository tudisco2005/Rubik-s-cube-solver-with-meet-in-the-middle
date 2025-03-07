#ifndef UTILS_H
#define UTILS_H

#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_WHITE   "\x1b[37m"
#define ANSI_COLOR_RESET   "\x1b[0m"

#define PRINT_YELLOW(x) printf("%s%s%s ", ANSI_COLOR_YELLOW, x, ANSI_COLOR_RESET);
// Remove the duplicate PRINT_YELLOW definition below
#define PRINT_RED(x) printf("%s%s%s ", ANSI_COLOR_RED, x, ANSI_COLOR_RESET);
#define PRINT_GREEN(x) printf("%s%s%s ", ANSI_COLOR_GREEN, x, ANSI_COLOR_RESET);
#define PRINT_BLUE(x) printf("%s%s%s ", ANSI_COLOR_BLUE, x, ANSI_COLOR_RESET);
#define PRINT_MAGENTA(x) printf("%s%s%s ", ANSI_COLOR_MAGENTA, x, ANSI_COLOR_RESET);
#define PRINT_WHITE(x) printf("%s%s%s ", ANSI_COLOR_WHITE, x, ANSI_COLOR_RESET);

void shift_array(int* arr, int size, int k);

#endif // UTILS_H