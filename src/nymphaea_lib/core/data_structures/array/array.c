#include"pch.h"
#include"array.h"

void np_array_create(np_array* array, size_t size, size_t type_size) {
    // allocate memory for buffer
    array->data = malloc(size * type_size);
    np_assert(array->data != NULL, "np_array: malloc error");
    // set whole array to null value
    memset(array->data, 0, size * type_size);
    // set other variables
    array->buffer_size = size;
    array->type_size = type_size;
}

void np_array_delete(np_array* array) {
    // free buffer
    free(array->data);
    // set variables to default
    array->data = NULL;
    array->buffer_size = 0;
    array->type_size = 0;
}

void* np_array_data(np_array* array) {
    return (unsigned char*)array->data;
}

void* np_array_get(np_array* array, size_t index) {
    // check if index is not out of range. if yes return NULL pointer.
    if (index >= array->buffer_size) return NULL;
    // return pointer to element at index
    return (unsigned char*)array->data + index * array->type_size;
}

void np_array_set(np_array* array, size_t index, void* data) {
    // check if index is not out of range. if yes cancel the operation.
    if (index >= array->buffer_size) return;
    // copy data into array
    memcpy((unsigned char*)array->data + index * array->type_size, data, array->type_size);
}

void np_array_clear(np_array* array) {
    // set whole array to null value
    memset(array->data, 0, array->buffer_size * array->type_size);
}

size_t np_array_get_size(np_array* array) {
    return array->buffer_size;
}
size_t np_array_get_size_bytes(np_array* array) {
    return array->buffer_size * array->type_size;
}

// TODO: maybe set new data to null?
void np_array_resize(np_array* array, size_t size) {
    // reallocate array to new position in memory with new size.
    array->data = realloc(array->data, array->type_size * size);
    // check if reallocation succeeded
    np_assert(array->data != NULL, "np_array: realloc error");
    // update array size
    array->buffer_size = size;
}