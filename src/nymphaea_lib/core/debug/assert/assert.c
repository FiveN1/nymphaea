#include"pch.h"
#include"assert.h"

void _np_assert(int condition, const char* file, int line, const char* message, ...) {
    if (condition) return;
    va_list args;
    va_start(args, message);
    char* msg = stringf(message, args);
    va_end(args);
    // log message
    np_printc(CONCOL_RED, msg); // np_print_red(msg); // jinak hází error v vs code
    np_print_red("at: %s line: %d", file, line);
    // clear message
    stringffree(msg);
    // abort program
    abort();
}