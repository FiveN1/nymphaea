#ifndef NP_ARRAY_H
#define NP_ARRAY_H

// array.h by FiveN

// ## Array
// - the simplest data structure.
// - array stores data together in one buffer on heap memory.
// - allows to loop over data stored in array.
// - array can be resized using 'np_array_resize'. NOTE: the data address will change if this functon is used.
typedef struct np_array {
    void* data;
    size_t buffer_size;
    size_t type_size;
} np_array;

// set array values like its data on the heap.
// - np_array* array  -> array instance.
// - size_t size      -> number of elements array can hold. (size of array)
// - size_t type_size -> size (in bytes) of element to be stored in array.
void np_array_create(np_array* array, size_t size, size_t type_size);
// free array memory.
// - np_array* array -> array instance.
void np_array_delete(np_array* array);
// get pointer to the array on the heap.
// - np_array* array -> array instance.
void* np_array_data(np_array* array);
// get pointer to data at index in the array.
// - np_array* array -> array instance.
// - size_t index    -> position (index) of elemnt in array.
void* np_array_get(np_array* array, size_t index);
// set data in the array to a value by copying from pointer
// - np_array* array -> array instance.
// - size_t index    -> position (index) of elemnt in array.
// - void* data      -> pointer to data to copy into array.
void np_array_set(np_array* array, size_t index, void* data);
// clear whole array.
// - np_array* array -> array instance.
void np_array_clear(np_array* array);
// get array size.
// - np_array* array -> array instance.
size_t np_array_get_size(np_array* array);
// get array size in bytes.
// - np_array* array -> array instance.
size_t np_array_get_size_bytes(np_array* array);
// resize array to new size, while keeping the old data.
// NOTE: the addresses of data in the array will change!
// - np_array* array -> array instance.
// - size_t size     -> new size of array.
void np_array_resize(np_array* array, size_t size);

#endif NP_ARRAY_H