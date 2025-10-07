#ifndef STRING_FORMAT_H
#define STRING_FORMAT_H

// formátuje const char* pomocí args
char* stringf(const char* formtat, va_list args);
// uvolní stringf output
void stringffree(char* string);

// vytovří kopii stringu na jiné adresse pomocí malloc()
// #### Tip: 
// - musí se uvolnit pomocí free()
// #### Parametry:
// - char* string -> adresa stringu kterou cheme allocovat.
char* np_string_allocate_copy(char* string);

#endif STRING_FORMAT_H