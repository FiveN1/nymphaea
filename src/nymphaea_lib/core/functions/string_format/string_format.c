#include"pch.h"
#include"string_format.h"

char* stringf(const char* formtat, va_list args) {
    // credit: https://stackoverflow.com/questions/66094905/how-to-pass-a-formatted-string-as-a-single-argument-in-c
    int len = vsnprintf(NULL, 0, formtat, args);
    if(len < 0) 
        return NULL;
    // format message
    char* string = malloc(sizeof(char) * (len + 1)); //[len + 1]; // or use heap allocation if implementation doesn't support VLAs
    vsnprintf(string, len + 1, formtat, args);
    return string;
}

void stringffree(char* string) {
    free(string);
}

char* np_string_allocate_copy(char* string) {
    // allocate string
    char* string_copy = malloc((strlen(string) + 1) * sizeof(char));
    // copy string data
    strcpy(string_copy, string);
    // return
    return string_copy;
}
