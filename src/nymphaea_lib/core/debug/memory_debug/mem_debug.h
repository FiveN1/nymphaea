#ifndef MEM_DEBUG_H
#define MEM_DEBUG_H

/*
*
* FiveN
*
* - Memory debug funkce pro snadné detekování memory leaku
*
* - Přidat aby free() smazal msg v logu po malloc
* - FILE WRITING IS NOT SAFE!!
*
* UPDATE
* - 08.08.2024
*
*/

// log memory allocation
void* malloc_debug(size_t size, const char* file, int line);
// log memory free
void free_debug(void* block, const char* file, int line);

//#define MEMORY_DEBUG
// Povolí memory debug funkce
#ifdef MEMORY_DEBUG
// Vymění malloc() za debug verzi této funkce
#define malloc(size) malloc_debug(size, __FILE__, __LINE__)
// vymění free() za debug verzi této funkce
#define free(block) free_debug(block, __FILE__, __LINE__)
#endif

#endif MEM_DEBUG_H