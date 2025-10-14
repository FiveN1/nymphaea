#include"pch.h"
#include"print.h"

void np_printc(unsigned short variant, const char* message, ...) {
    // format string
    va_list args;
    va_start(args, message);
    char* msg = stringf(message, args);
    va_end(args);
    // call bound function
    (*g_np_log_callback)(msg, variant);
    // clear memory
    stringffree(msg);
} 

#ifdef NP_PLATFORM_WINDOWS

// default console print function on windows
void np_default_print_callback(const char* message, unsigned short variant) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), variant);
    printf("[%f] %s\n", np_get_time(), message);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), CONCOL_WHITE);
}
#else

// default console print function on other os
void np_default_print_callback(const char* message, unsigned short variant) {
    printf("%s\n", message);
}

#endif

// set default global callback 
np_print_callback g_np_log_callback = &np_default_print_callback;

void np_print_set_callback(np_print_callback callback) {
    g_np_log_callback = callback;
}