#include"pch.h"
#include"log.h"

//
// default log callback function
//

void default_log_function(const char* message, unsigned short variant);

#ifdef NP_PLATFORM_WINDOWS

void default_log_function(const char* message, unsigned short variant) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), variant);
    printf("[%f] %s\n", np_get_time(), message);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), CONCOL_WHITE);
}
#else

void default_log_function(const char* message, unsigned short variant) {
    printf("%s\n", message);
}
#endif

// set default global callback 
np_log_callback g_np_log_callback = &default_log_function;

//
// function definition from log.h
//

void np_log_set_callback(np_log_callback callback) {
    g_np_log_callback = callback;
}

void np_logf(unsigned short variant, const char* message, ...) {
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