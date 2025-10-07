#ifndef NP_FILE_H
#define NP_FILE_H

#include"nymphaea_lib/core/data_structures/array/array.h"
#include"nymphaea_lib/core/data_structures/dynamic_array/dynamic_array.h"

/*
* file.h
*
* functions for manipulating files
*
*
*/

// read file as string
char* np_file_load(const char* filename);
// free read file
void np_file_free(char* file_content);

//bool np_file_find(const char* filename);


char* np_file_load_w(const wchar_t* filename);


//np_dynamic_array np_file_get_files_w(const wchar_t* directory, const wchar_t* filemask);

// find files in directory using specified filemask
// 'directory' must include the filemansk. (example: C:\Folder\*.c)
// returning array of 'WIN32_FIND_DATA' wich holds data about files
// use file attributes to check if is a folder or file: https://learn.microsoft.com/en-us/windows/win32/fileio/file-attribute-constants
WIN32_FIND_DATA* np_file_find_w(const wchar_t* directory, size_t* return_size);

bool np_file_find_check_if_folder(WIN32_FIND_DATA find_file_data);

// writes current working directory (directory in wich the program sits) to a buffer.
// #### Parameters
// char* buffer       -> a buffer in wich the directory will be written
// size_t buffer_size -> size of buffer
void np_get_work_directory(char* buffer, size_t buffer_size);

// writes absolute directory to buffer with local directory
//void np_local_directory(char* buffer, char* local_directory);

// get parent directory of file
// C:/folder/file.c -> C:/folder/
void np_get_parent_directory(char* buffer, size_t buffer_size, const char* filename);


// https://stackoverflow.com/questions/8487986/file-macro-shows-full-path


//np_dynamic_array np_file_get_folders_w(const wchar_t* directory, const wchar_t* filemask);


/*
* Změny
* [27.05.2025] přidáno np_get_work_directory();
*
*
*
*
**/

#endif NP_FILE_H