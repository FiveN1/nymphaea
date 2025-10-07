#ifndef NP_ASSERT_H
#define NP_ASSERT_H

/*
* assert.h
* - this file contains the macro & function for assertion
* - useful for debuggung
*
* UPDATE:
* - 08.09.2024 - written
*/

// abort program if condition is false
#define np_assert(condition, message, ...) _np_assert(condition, __FILE__, __LINE__, message, __VA_ARGS__);
// assert function not for use!
void _np_assert(int condition, const char* file, int line, const char* message, ...);

#endif NP_ASSERT_H