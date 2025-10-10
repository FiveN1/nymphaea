#ifndef NP_LOG_H 
#define NP_LOG_H

// include the color codes
#include"nymphaea_lib/os/console/console.h"

/*
* log.h
* - this file contains all functions used for logging a message to anything you like
* - by default the message will be logged to console
* - the default log will include a timer. NOTE: logging a message takes about 17ms
*
* UPDATE
* - 08.09.2024 - written
* - 08.09.2024 - removed log callback list & replaced with one single function callback
* - 10.09.2024 - added timer in ms to logged message
*/

//
// Global log callback
//

// Log callback type function pointer
// first arg is the message
// the second passes the color value
typedef void (*np_log_callback)(const char*, unsigned short);
// global log callback for the whole program
// NOTE: g_log_callback is set to default callback in log.c
extern np_log_callback g_np_log_callback;
// set log output
void np_log_set_callback(np_log_callback callback);

//
// Macro
//

// define log macros if in debug
#ifdef NP_DEBUG
// Log a formated message
#define np_log(message, ...) np_logf(CONCOL_WHITE, message, __VA_ARGS__)
// Log a success formated message
#define np_log_sucess(message, ...) np_logf(CONCOL_GREEN, message, __VA_ARGS__)
// Log a warn formated message
#define np_log_warn(message, ...) np_logf(CONCOL_YELLOW, message, __VA_ARGS__)
// Log a error formated message
#define np_log_error(message, ...) np_logf(CONCOL_RED, message, __VA_ARGS__)



#define np_debug_print(message, ...) np_logf(CONCOL_WHITE, message, __VA_ARGS__)

#define np_debug_print_green(message, ...) np_logf(CONCOL_GREEN, message, __VA_ARGS__)

#define np_debug_print_yellow(message, ...) np_logf(CONCOL_YELLOW, message, __VA_ARGS__)

#define np_debug_print_red(message, ...) np_logf(CONCOL_RED, message, __VA_ARGS__)

#define np_debug_print_blue(message, ...) np_logf(CONCOL_BLUE, message, __VA_ARGS__)

#define np_debug_print_aqua(message, ...) np_logf(CONCOL_AQUA, message, __VA_ARGS__)

#define np_debug_print_purple(message, ...) np_logf(CONCOL_PURPLE, message, __VA_ARGS__)

#else
// Log a formated message
#define np_log(message, ...)
// Log a success formated message
#define np_log_sucess(message, ...)
// Log a warn formated message
#define np_log_warn(message, ...)
// Log a error formated message
#define np_log_error(message, ...)



#define np_debug_print(message, ...)

#define np_debug_print_green(message, ...)

#define np_debug_print_yellow(message, ...)

#define np_debug_print_red(message, ...)

#define np_debug_print_blue(message, ...)

#define np_debug_print_aqua(message, ...)

#define np_debug_print_purple(message, ...)

#endif

//
// NOT DEBUG
//

#define np_print(message, ...) np_logf(CONCOL_WHITE, message, __VA_ARGS__)

#define np_print_green(message, ...) np_logf(CONCOL_GREEN, message, __VA_ARGS__)

#define np_print_yellow(message, ...) np_logf(CONCOL_YELLOW, message, __VA_ARGS__)

#define np_print_red(message, ...) np_logf(CONCOL_RED, message, __VA_ARGS__)

#define np_print_blue(message, ...) np_logf(CONCOL_BLUE, message, __VA_ARGS__)

#define np_print_aqua(message, ...) np_logf(CONCOL_AQUA, message, __VA_ARGS__)

#define np_print_purple(message, ...) np_logf(CONCOL_PURPLE, message, __VA_ARGS__)

//
// Functions
//

// Send formated message to callback
void np_logf(unsigned short variant, const char* message, ...);

/*
* Změny
*
* [07.06.2025] přidán np_debug_print(), důvod? ->
* - všechny debug funnkce budou začínat s np_debug_.
* - také je z toho jasné že jde o print, protože log se v názvosloví nepoužívá.
* - za np_debug_print je pak vložena barva v které bude vytisknut text.
* [09.10.2025] přidány klasické np_print() funkce, které zůstanou i v release.
*
*
*
*
*
*
*
*/

#endif NP_LOG_H