#ifndef NP_FILE_H
#define NP_FILE_H

/*
* file.h
*
* functions for manipulating files
*
*/

// open a file.
// #### Parameters:
// - const char* filename -> file directory.
// #### Return:
// - FILE* -> file handle. NOTE: needs to be cleared with np_file_close() !
FILE* np_file_open(const char* filename);

// close a file after opening.
// #### Parameters:
// - FILE* file -> file handle.
void np_file_close(FILE* file);

// get file content size in bytes.
// #### Parameters:
// - FILE* file -> file handle.
// #### Return:
// - long -> file size.
long np_file_get_size(FILE* file);

// loads filedata to memory.
// #### Parametry:
// - FILE* file -> file handle.
// - void* buffer -> buffer into wich the file content will be written.
// - long buffer_size -> buffer size.
void np_file_load(FILE* file, void* buffer, long buffer_size);

// načte data souboru jako string.
// NOTE: string needs to be freed!
// #### Parametry:
// - const char* filename -> cesta k souboru.
// #### Return:
// - char* -> pointer na string dat souboru. (na heapu)
char* np_file_load_string(FILE* file);

/*
* Změny
* [27.05.2025] 
* přidáno np_get_work_directory();
*
* [14.10.2025] 
* cleanup, přidány basic funkce, teď se vše orientuje kolem file handle.
*
*/

#endif NP_FILE_H