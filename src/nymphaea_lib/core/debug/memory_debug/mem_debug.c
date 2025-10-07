#include"pch.h"
#include"mem_debug.h"

void fnewifnot(const char* filename) {
    FILE* file;
    if (fopen_s(&file, filename, "r")) 
        fopen_s(&file, filename, "w+");
    fclose(file);
}

void* malloc_debug(size_t size, const char* file, int line) {
    // call malloc
    #undef malloc // guard
    void* ptr = malloc(size);
    #define malloc(size) malloc_debug(size, __FILE__, __LINE__)

    // Write log
    fnewifnot("mem_debug_log.txt");
    FILE* filetxt;
    np_assert(!fopen_s(&filetxt, "mem_debug_log.txt", "a"), "cant open file");
    fprintf_s(filetxt, "m %p file: %s line: %d\n", ptr, file, line);
    fclose(filetxt);

    return ptr;
}

void free_debug(void* block, const char* file, int line) {
    // call free
    #undef free // guard
    free(block);
    #define free(block) free_debug(block, __FILE__, __LINE__)

    // Write log
    fnewifnot("mem_debug_log.txt");
    FILE* filetxt;
    np_assert(!fopen_s(&filetxt, "mem_debug_log.txt", "a"), "cant open file");
    fprintf_s(filetxt, "f %p file: %s line: %d\n", block, file, line);

    fclose(filetxt);
}