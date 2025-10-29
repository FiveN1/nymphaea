#include"pch.h"
#include"file.h"

FILE* np_file_open(const char* filename) {
    FILE* file;
    // open file
    errno_t err;
    if ((err = fopen_s(&file, filename, "r")) == 0) return file;
    // if could not open file then return null
    np_file_close(file);
    return NULL;
}

void np_file_close(FILE* file) {
    fclose(file);
}

long np_file_get_size(FILE* file) {
    fseek(file, 0L, SEEK_END);
    long file_size = ftell(file);
    fseek(file, 0L, SEEK_SET);
    return file_size;
}

void np_file_load(FILE* file, void* buffer, long buffer_size) {
    // read filedata to memory
    fread(buffer, sizeof(unsigned char), buffer_size, file);
}

char* np_file_load_string(FILE* file) {
    // get file length
    long file_size = np_file_get_size(file);
    // allocate memory for the file content
    // add 1 extra space for the terminator character
    char* file_data = (char*)malloc(sizeof(char) * (file_size + 1));
    if (file_data == NULL) {
        np_debug_print_red("np_file_load: malloc error!");
        return NULL;
    }
    // read the whole file into the buffer
    size_t file_size_loaded = fread(file_data, sizeof(char), file_size, file);
    // set the terminator
    // the terminator may not be necessarily at the end of the buffer
    file_data[file_size_loaded] = '\0';
    // return
    return file_data;
}

void np_get_work_directory(char* buffer, size_t buffer_size) {
    np_assert(getcwd(buffer, buffer_size) != NULL, "getcwd error");
}

void np_get_parent_directory(char* buffer, size_t buffer_size, const char* filename) {
    _splitpath_s(filename, NULL, 0, buffer, buffer_size, NULL, 0, NULL, 0);  
}
