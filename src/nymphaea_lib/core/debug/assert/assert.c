#include"pch.h"
#include"assert.h"
#include"nymphaea_lib/core/string/string.h"

void _np_assert(int condition, const char* file, int line, const char* message, ...) {
    if (condition) return;
    va_list args;
    va_start(args, message);
    char* msg = np_stringf(message, args);
    va_end(args);
    // log message
    np_printc(CONCOL_RED, msg); // np_print_red(msg); // jinak hází error v vs code
    np_print_red("at: %s line: %d", file, line);
    // free message data
    free(msg);
    // abort program
    abort();
}