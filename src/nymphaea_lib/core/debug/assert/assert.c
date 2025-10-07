#include"pch.h"
#include"assert.h"

void _np_assert(int condition, const char* file, int line, const char* message, ...) {
    if (condition) return;
    va_list args;
    va_start(args, message);
    char* msg = stringf(message, args);
    va_end(args);
    // log message
    np_log_error(msg);             
    np_log_error("at: %s line: %d", file, line);
    // clear message
    stringffree(msg);
    // abort program
    abort();
}