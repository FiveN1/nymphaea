#include"pch.h"
#include"directory.h"


void np_directory_get_parent(const char* directory, char* buffer, size_t buffer_size) {
    _splitpath_s(directory, NULL, 0, buffer, buffer_size, NULL, 0, NULL, 0);  
}

void np_directory_get_working(char* buffer, size_t buffer_size) {
    np_assert(getcwd(buffer, buffer_size) != NULL, "np_directory_get_working: getcwd error");
}