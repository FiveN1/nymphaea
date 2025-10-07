#ifndef NP_DYNAMIC_FRAG_ARRAY_H
#define NP_DYNAMIC_FRAG_ARRAY_H

#include"pch.h"

/*
* ## Dynamic Fragmented Array
* fragmented array that can dynamically resize its capacity.
*
* ## Pros / Cons
* + keeps indicies of data in the array.
* + is not limited to size.
* + fastly adds and removes data from array.
* - does not keep data address.
* - after many changes is not fast to iterate upon, because of fragmentation.
*
*/
typedef struct np_dynamic_frag_array { 
    // buffers
    void* data_buffer;
    size_t* element_buffer;
    bool* boolean_buffer;
    // NOTE: all buffers are the same size
    size_t buffer_size;
    size_t type_size;
    size_t size;
} np_dynamic_frag_array;

// create dynamic fragmented array
void np_dynamic_frag_array_create(np_dynamic_frag_array* dynamic_frag_array, size_t type_size);
// delete dynamic fragmented array
void np_dynamic_frag_array_delete(np_dynamic_frag_array* dynamic_frag_array);
// add data to dynamic fragmented array and get its index via 'return_index'. (NULL can be passed to 'return_index')
// set the data with the returning pointer
// NOTE: pointer is not constant!
void* np_dynamic_frag_array_add(np_dynamic_frag_array* dynamic_frag_array, size_t* return_index);
// copy data to dynamic fragmented array
size_t np_dynamic_frag_array_add_copy(np_dynamic_frag_array* dynamic_frag_array, const void* data);
// add empty data to dynamic fragmented array
size_t np_dynamic_frag_array_add_empty(np_dynamic_frag_array* dynamic_frag_array);
// remove data from dynamic fragmented array
void np_dynamic_frag_array_remove(np_dynamic_frag_array* dynamic_frag_array, size_t index);
// get data from dynamic fragmented array
void* np_dynamic_frag_array_get(np_dynamic_frag_array* dynamic_frag_array, size_t index);
// get index of data in dynamic fragmented array. input index goes from 0 to 'np_dynamic_frag_array_get_size'
size_t np_dynamic_frag_array_get_index(np_dynamic_frag_array* dynamic_frag_array, size_t index);
// get current size of dynamic fragmented array
size_t np_dynamic_frag_array_get_size(np_dynamic_frag_array* dynamic_frag_array);
// resize dynamic fragmented array
void np_dynamic_frag_array_resize(np_dynamic_frag_array* dynamic_frag_array, size_t new_size);

#endif NP_DYNAMIC_FRAG_ARRAY_H