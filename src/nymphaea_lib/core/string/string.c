#include"pch.h"
#include"string.h"

char* np_stringf(const char* format, va_list args) {
    // credit: https://stackoverflow.com/questions/66094905/how-to-pass-a-formatted-string-as-a-single-argument-in-c
    int len = vsnprintf(NULL, 0, format, args);
    if(len < 0) 
        return NULL;
    // format message
    char* string = malloc(sizeof(char) * (len + 1)); //[len + 1]; // or use heap allocation if implementation doesn't support VLAs
    vsnprintf(string, len + 1, format, args);
    return string;
}