#ifndef NP_PRINT_H 
#define NP_PRINT_H

/*
* log.h
*
* this file contains all functions used for logging a message to anything you like
* by default the message will be logged to console
* the default log will include a timer. NOTE: logging a message takes about 17ms
*
*/

// send colored formated message to callback.
// #### Parameters:
// - unsigned short variant -> color variant.
// - const char* message -> message you want to print.
// - ... -> format for the message.
void np_printc(unsigned short variant, const char* message, ...);

// print callback type function pointer
// #### Parameters:
// - const char* message -> input message.
// - unsigned short variant -> color variant.
typedef void (*np_print_callback)(const char*, unsigned short);

// global print callback for the whole program
// NOTE: by default is set to np_default_print_callback()
extern np_print_callback g_np_log_callback;

// default nymphaea print function.
// #### Parameters:
// - const char* message -> input message.
// - unsigned short variant -> color variant.
void np_default_print_callback(const char* message, unsigned short variant);

// set print output
// #### Parameters:
// - np_print_callback callback -> callback function that will be called on every np_print()
void np_print_set_callback(np_print_callback callback);

// print color variants.

#define CONCOL_BLACK    0x0000
#define CONCOL_BLUE     0x0001
#define CONCOL_GREEN    0x0002
#define CONCOL_AQUA     0x0003
#define CONCOL_RED      0x0004
#define CONCOL_PURPLE   0x0005
#define CONCOL_YELLOW   0x0006
#define CONCOL_WHITE    0x0007

// print macros

#define np_print(message, ...) np_printc(CONCOL_WHITE, message, __VA_ARGS__)
#define np_print_green(message, ...) np_printc(CONCOL_GREEN, message, __VA_ARGS__)
#define np_print_yellow(message, ...) np_printc(CONCOL_YELLOW, message, __VA_ARGS__)
#define np_print_red(message, ...) np_printc(CONCOL_RED, message, __VA_ARGS__)
#define np_print_blue(message, ...) np_printc(CONCOL_BLUE, message, __VA_ARGS__)
#define np_print_aqua(message, ...) np_printc(CONCOL_AQUA, message, __VA_ARGS__)
#define np_print_purple(message, ...) np_printc(CONCOL_PURPLE, message, __VA_ARGS__)

// define print macros

#ifdef NP_DEBUG
#define np_debug_print(message, ...) np_printc(CONCOL_WHITE, message, __VA_ARGS__)
#define np_debug_print_green(message, ...) np_printc(CONCOL_GREEN, message, __VA_ARGS__)
#define np_debug_print_yellow(message, ...) np_printc(CONCOL_YELLOW, message, __VA_ARGS__)
#define np_debug_print_red(message, ...) np_printc(CONCOL_RED, message, __VA_ARGS__)
#define np_debug_print_blue(message, ...) np_printc(CONCOL_BLUE, message, __VA_ARGS__)
#define np_debug_print_aqua(message, ...) np_printc(CONCOL_AQUA, message, __VA_ARGS__)
#define np_debug_print_purple(message, ...) np_printc(CONCOL_PURPLE, message, __VA_ARGS__)
#else
#define np_debug_print(message, ...)
#define np_debug_print_green(message, ...)
#define np_debug_print_yellow(message, ...)
#define np_debug_print_red(message, ...)
#define np_debug_print_blue(message, ...)
#define np_debug_print_aqua(message, ...)
#define np_debug_print_purple(message, ...)
#endif

/*
* Změny
*
* [08.09.2024] 
* written.
* removed log callback list & replaced with one single function callback
*
* [10.09.2024] 
* added timer in ms to logged message
*
* [14.10.2025] 
* renamed to np_print, cleanup.
* tady už česky :D
*
* [07.06.2025] 
* přidán np_debug_print(), důvod? ->
* - všechny debug funnkce budou začínat s np_debug_.
* - také je z toho jasné že jde o print, protože log se v názvosloví nepoužívá.
* - za np_debug_print je pak vložena barva v které bude vytisknut text.
*
* [09.10.2025]
*  přidány klasické np_print() funkce, které zůstanou i v release.
*
* [14.10.2025]
* přejmenováno na np_print, cleanup. teď je vše parádní.
*
*/

#endif NP_PRINT_H