#ifndef NP_DYNAMIC_ARRAY
#define NP_DYNAMIC_ARRAY

#include"pch.h"

// dynamic_array.h by FiveN

/*
* ## Dynamic Array
* This type of array is almosi identical to 'np_array' but it is not limited with a defined size.
* This array will change its size if there are more elements added then it can hold. hence why its called 'dynamic'
* 
* NOTE:
* Do not point to memory in this array because the address is not constant!
*
* ### Related functions
* - np_dynamic_array_create
* - np_dynamic_array_delete
* - np_dynamic_array_add
* - np_dynamic_array_pop
* - np_dynamic_array_insert
* - np_dynamic_array_remove
* - np_dynamic_array_get
* - np_dynamic_array_get_size
* - np_dynamic_array_resize
* - np_dynamic_array_clear
*
* ### Performence
* 'np_dynamic_array is slower than 'np_array' because the whole buffer needs to be reallocated when adding data to it.
* this can be mitigated by pre-allocating the array with 'np_dynamic_array_resize'
* this array is also stored only on the heap.
*
*/
typedef struct np_dynamic_array {
    void* data;
    size_t block_size;
    size_t type_size;
    size_t size;
} np_dynamic_array;

// create a dynamic array with a defined size of data type held in the array
void np_dynamic_array_create(np_dynamic_array* dynamic_array, size_t type_size);
// delete dynamic array data
void np_dynamic_array_delete(np_dynamic_array* dynamic_array);
// add data to the aray at the end
void* np_dynamic_array_add(np_dynamic_array* dynamic_array);
// add copied data to the aray at the end
void np_dynamic_array_add_copy(np_dynamic_array* dynamic_array, const void* data);
// remove the very last piece of data in the array
void np_dynamic_array_pop(np_dynamic_array* dynamic_array);
// insert any data at any position in the array.
void np_dynamic_array_insert(np_dynamic_array* dynamic_array, size_t index, const void* data);
// remove any data from the array at index
void np_dynamic_array_remove(np_dynamic_array* dynamic_array, size_t index);
// get a pointer to the data in the array at index
void* np_dynamic_array_get(np_dynamic_array* dynamic_array, size_t index);
// get the current size of the array
size_t np_dynamic_array_get_size(np_dynamic_array* dynamic_array);
// reallocate the array to a new size
// if the array shrinks the data outside of new size will be deleted
void np_dynamic_array_resize(np_dynamic_array* dynamic_array, size_t new_size);
// set array size to 0
void np_dynamic_array_clear(np_dynamic_array* dynamic_array);

#endif NP_DYNAMIC_ARRAY