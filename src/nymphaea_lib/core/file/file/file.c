#include"pch.h"
#include"file.h"

// tohle je POUZE pro windows !!
// ostatní použivají: #include <unistd.h>
#include <direct.h>


long np_file_get_size(FILE* file) {
    fseek(file, 0L, SEEK_END);
    long file_size = ftell(file);
    fseek(file, 0L, SEEK_SET);
    return file_size;
}

unsigned char* np_file_load(const char* filename, long* file_data_size) {
    FILE* file;
    errno_t err;
    if ((err = fopen_s(&file, filename, "r")) != 0) {
        np_debug_print_red("np_file_load error: file \"%s\" not found!", filename);
        fclose(file);
        return NULL;
    }
    // get file length
    *file_data_size = np_file_get_size(file);
    np_debug_print("dgdsf: %llu", sizeof(unsigned char) * (size_t)(*file_data_size));

    unsigned char* file_data = (unsigned char*)malloc(sizeof(unsigned char) * (size_t)(*file_data_size));
    if (file_data == NULL) {
        np_debug_print_red("np_file_load error: malloc error!");
        fclose(file);
        return NULL;
    }

    fread(file_data, sizeof(unsigned char), *file_data_size, file);

    fclose(file);
    
    return file_data;
}

/*
* NOTE:
* the return value of malloc & fread is not checked!
* this function is not well buit!
*/
char* np_file_load_string(const char* filename) {
    // get file handler and check if file exists
    FILE* file;
    errno_t err;
    if ((err = fopen_s(&file, filename, "r")) != 0) {
        np_debug_print_red("np_file error: file \"%s\" not found!", filename);
        return NULL;
    }
    // get file length
    long file_size = np_file_get_size(file);
    // allocate memory for the file content
    // add 1 extra space for the terminator character
    char* file_content = (char*)malloc(sizeof(char) * (file_size + 1));
    // read the whole file into the buffer
    size_t file_size_loaded = fread(file_content, sizeof(char), file_size, file);
    // set the terminator
    // the terminator may not be necessarily at the end of the buffer
    file_content[file_size_loaded] = '\0';
    // close file and return the file content
    fclose(file);
    return file_content;
}

char* np_file_load_string_w(const wchar_t* filename) {
    // get file handler and check if file exists
    FILE* file;
    errno_t err;
    if ((err = _wfopen_s(&file, filename, L"r")) != 0) return NULL;
    // get file length
    fseek(file, 0L, SEEK_END);
    long file_size = ftell(file);
    fseek(file, 0L, SEEK_SET);
    // allocate memory for the file content
    // add 1 extra space for the terminator character
    char* file_content = (char*)malloc(sizeof(char) * (file_size + 1));
    // read the whole file into the buffer
    size_t file_size_loaded = fread(file_content, sizeof(char), file_size, file);
    // set the terminator
    // the terminator may not be necessarily at the end of the buffer
    file_content[file_size_loaded] = '\0';
    // close file and return the file content
    fclose(file);
    return file_content;
}

void np_file_free(char* file_data) {
    free(file_data);
}

/*

np_dynamic_array np_file_get_files_w(const wchar_t* directory, const wchar_t* filemask) {
    // returning array
    np_dynamic_array dynamic_array;
    np_dynamic_array_create(&dynamic_array, sizeof(wchar_t[2048]));
    //
    WIN32_FIND_DATA find_data_file; 
    HANDLE handle_find = NULL; 
    wchar_t path[2048]; 
    // specify the filemask
    wsprintf(path, L"%s\\%s", directory, filemask); // "c:/file/ + *.c"
    // set the handle
    if((handle_find = FindFirstFile(path, &find_data_file)) == INVALID_HANDLE_VALUE) { 
        np_log("path not found");
        return dynamic_array;
    } 
    do { 
        //Find first file will always return "."
        //    and ".." as the first two directories. 
        if (wcscmp(find_data_file.cFileName, L".") != 0 && wcscmp(find_data_file.cFileName, L"..") != 0) { 
            //Build up our file path using the passed in 
            //  [sDir] and the file/foldername we just found: 
            wsprintf(path, L"%s\\%s", directory, find_data_file.cFileName); 
            // check if is a file
            // file attributes: https://learn.microsoft.com/en-us/windows/win32/fileio/file-attribute-constants
            if (!(find_data_file.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)) {
                //wprintf(L"File: %s\n", path); 

                np_dynamic_array_add_copy(&dynamic_array, &path);
            }

        }
    } while(FindNextFile(handle_find, &find_data_file)); //Find the next file. 

    FindClose(handle_find);
    return dynamic_array;
}
*/

WIN32_FIND_DATA* np_file_find_w(const wchar_t* directory, size_t* return_size) {
    // create a dynamic array so we can resize it when we find a file
    // TODO: change this to just an array !
    np_dynamic_array files;
    np_dynamic_array_create(&files, sizeof(WIN32_FIND_DATA));
    // setup find data
    WIN32_FIND_DATA file_find_data;
    HANDLE handle_find = NULL; 
    // set the handle
    if ((handle_find = FindFirstFile(directory, &file_find_data)) == INVALID_HANDLE_VALUE) { 
        np_log_error("np_file_find_w error: path not found");
        // make sure to free allocated memory
        np_dynamic_array_delete(&files);
        *return_size = 0;
        // return empty array
        return NULL;
    } 
    // find files in directory
    do { 
        // find first file will always return ".", and ".." as the first two directories. 
        if (wcscmp(file_find_data.cFileName, L".") != 0 && wcscmp(file_find_data.cFileName, L"..") != 0) { 
            // add find file data to array
            np_dynamic_array_add_copy(&files, &file_find_data);
        }
    } while(FindNextFile(handle_find, &file_find_data));
    // close handle
    FindClose(handle_find);
    // return array
    *return_size = np_dynamic_array_get_size(&files);
    return (WIN32_FIND_DATA*)np_dynamic_array_get(&files, 0);
}

bool np_file_find_check_if_folder(WIN32_FIND_DATA file_find_data) {
    return (file_find_data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY);
}


void np_get_work_directory(char* buffer, size_t buffer_size) {
    np_assert(getcwd(buffer, buffer_size) != NULL, "getcwd error");
}

void np_get_parent_directory(char* buffer, size_t buffer_size, const char* filename) {
    _splitpath_s(filename, NULL, 0, buffer, buffer_size, NULL, 0, NULL, 0);  
}