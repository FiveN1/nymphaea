#ifndef NP_STRING_H
#define NP_STRING_H

/*
* string.h
*
* functions for string manipulation.
*
*/

// format string
// returned formated string is stored on the heap.
// #### Parameters:
// - const char* format -> string with format.
// - va_list args -> format variables.
// #### Return:
// - char* -> formated string.
char* np_stringf(const char* format, va_list args);

// converts a boolean type to string at compile time.
#define np_bool_to_str(state) &"true\0false"[5*!state];

/*
* ## Změny
*
* #### 14.10.2025
* vytvořeno.
* 
*
*/

#endif NP_STRING_H