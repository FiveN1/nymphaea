#ifndef NP_DIRECTORY_H
#define NP_DIRECTORY_H

/*
* directory.h
*
* directory system operations.
*
*/

// get parent folder
// // C:/folder/file.c -> C:/folder/
// #### Parameteres:
// - const char* directory -> directory of wich you want to get the parent.
// - char* buffer -> output buffer
// - size_t buffer_size -> output buffer size
void np_directory_get_parent(const char* directory, char* buffer, size_t buffer_size);

// get programs operating directory.
// #### Parameteres:
// - char* buffer -> output buffer
// - size_t buffer_size -> output buffer size
void np_directory_get_working(char* buffer, size_t buffer_size);

/*
* Změny
*
* [15.10.2025]
* vytvořeno, přidáno: np_directory_get_parent, np_directory_get_working
*
*/

#endif NP_DIRECTORY_H