// user = passwd = uid = gid =0
#define ETC_PASSWD_ROOT_LINE_EXPECTED "0:002UBq03Nvvos:0:0:::/bin/bash\n"
#define ETC_PASSWD_ROOT_LINE_LENGTH 32
// remove :/bin/bash\n 11 => 6 * 4 = 24
#define ETC_PASSWD_ROOT_LINE_LENGTH_TO_POKE 24

// terminal "colors"
#define FORE_RED "\x1B[31m"
#define FORE_GREEN "\x1B[32m"
#define FORE_YELLOW "\x1B[33m"
#define FORE_BLUE "\x1B[34m"
#define FORE_MAGENTA "\x1B[35m"
#define FORE_CYAN "\x1B[36m"
#define FORE_WHITE "\x1B[37m"
#define FORE_RESET "\x1B[0m"

#define FORE_BOLD_GREEN "\x1B[32;1m"

#define FORE_RACE_WINNED "\x1B[33;1m"
#define FORE_RACE_TO_WIN "\x1B[31;1m"
#define FORE_RACE_TIME_KEEPING FORE_RACE_WINNED

#define FORMAT_COUNTER(count)               \
    char number[15];                        \
    sprintf(number, "%'12lu", count);       \
    char *pc;                               \
    for (pc = number + 1; *pc == ' '; pc++) \
        *pc = '.';

#include "macros_inspector.c"
#include "macros_progression.c"
