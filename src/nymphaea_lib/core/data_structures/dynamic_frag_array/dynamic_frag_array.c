#include"pch.h"
#include"dynamic_frag_array.h"

// find avalible index in frragmented array
// NOTE: O(n) time complexity
size_t np_dynamic_frag_array_find_avalible_index(bool* boolean_array, size_t size);
// find value in array
// NOTE: O(n) time complexity
size_t np_dynamic_frag_array_find_value(size_t* element_array, size_t size, size_t value);

void np_dynamic_frag_array_create(np_dynamic_frag_array* dynamic_frag_array, size_t type_size) {
    dynamic_frag_array->data_buffer = NULL;
    dynamic_frag_array->element_buffer = NULL;
    dynamic_frag_array->boolean_buffer = NULL;
    dynamic_frag_array->buffer_size = 0;
    dynamic_frag_array->type_size = type_size;
    dynamic_frag_array->size = 0;
}

void np_dynamic_frag_array_delete(np_dynamic_frag_array* dynamic_frag_array) {
    // free buffers
    free(dynamic_frag_array->data_buffer);
    dynamic_frag_array->data_buffer = NULL;
    free(dynamic_frag_array->element_buffer);
    dynamic_frag_array->element_buffer = NULL;
    free(dynamic_frag_array->boolean_buffer);
    dynamic_frag_array->boolean_buffer = NULL;
    // set to default
    dynamic_frag_array->buffer_size = 0;
    dynamic_frag_array->type_size = 0;
    dynamic_frag_array->size = 0;
}

void* np_dynamic_frag_array_add(np_dynamic_frag_array* dynamic_frag_array, size_t* return_index) {
    dynamic_frag_array->size++;
    // if array cant hold any more data then call array resize
    // NOTE: array is only resized by 1 each time it reaches the limit.
    if (dynamic_frag_array->size > dynamic_frag_array->buffer_size) np_dynamic_frag_array_resize(dynamic_frag_array, dynamic_frag_array->size);
    // find avalible index in fragmented array
    size_t index = np_dynamic_frag_array_find_avalible_index(dynamic_frag_array->boolean_buffer, dynamic_frag_array->buffer_size);
    if (index == dynamic_frag_array->buffer_size) return NULL;
    // set null data
    memset((unsigned char*)dynamic_frag_array->data_buffer + index * dynamic_frag_array->type_size, 0, dynamic_frag_array->type_size);
    // update index status
    dynamic_frag_array->boolean_buffer[index] = true;
    // add index to element array
    dynamic_frag_array->element_buffer[dynamic_frag_array->size - 1] = index;
    // set return_index if not null
    if (return_index != NULL) *return_index = index;
    // return pointer to new memory in the fragmented array
    return (unsigned char*)dynamic_frag_array->data_buffer + index * dynamic_frag_array->type_size;
}

size_t np_dynamic_frag_array_add_copy(np_dynamic_frag_array* dynamic_frag_array, const void* data) {
    dynamic_frag_array->size++;
    // if array cant hold any more data then call array resize
    // NOTE: array is only resized by 1 each time it reaches the limit.
    if (dynamic_frag_array->size > dynamic_frag_array->buffer_size) np_dynamic_frag_array_resize(dynamic_frag_array, dynamic_frag_array->size);
    // find avalible index in fragmented array
    size_t index = np_dynamic_frag_array_find_avalible_index(dynamic_frag_array->boolean_buffer, dynamic_frag_array->buffer_size);
    if (index == dynamic_frag_array->buffer_size) return index;
    // copy the data to the fragmented array
    memcpy((unsigned char*)dynamic_frag_array->data_buffer + index * dynamic_frag_array->type_size, data, dynamic_frag_array->type_size);
    // update index status
    dynamic_frag_array->boolean_buffer[index] = true;
    // add index to element array
    dynamic_frag_array->element_buffer[dynamic_frag_array->size - 1] = index;
    // return index at wich the data is now located
    return index;
}

size_t np_dynamic_frag_array_add_empty(np_dynamic_frag_array* dynamic_frag_array) {
    dynamic_frag_array->size++;
    // if array cant hold any more data then call array resize
    // NOTE: array is only resized by 1 each time it reaches the limit.
    if (dynamic_frag_array->size > dynamic_frag_array->buffer_size) np_dynamic_frag_array_resize(dynamic_frag_array, dynamic_frag_array->size);
    // find avalible index in fragmented array
    size_t index = np_dynamic_frag_array_find_avalible_index(dynamic_frag_array->boolean_buffer, dynamic_frag_array->buffer_size);
    if (index == dynamic_frag_array->buffer_size) return index;
    // set null data
    memset((unsigned char*)dynamic_frag_array->data_buffer + index * dynamic_frag_array->type_size, 0, dynamic_frag_array->type_size);
    // update index status
    dynamic_frag_array->boolean_buffer[index] = true;
    // add index to element array
    dynamic_frag_array->element_buffer[dynamic_frag_array->size - 1] = index;
    // return index at wich the data is now located
    return index;
}

void np_dynamic_frag_array_remove(np_dynamic_frag_array* dynamic_frag_array, size_t index) {
    size_t index_of_index = np_dynamic_frag_array_find_value(dynamic_frag_array->element_buffer, dynamic_frag_array->size, index);
    // return if value does not exist in element buffer
    if (index_of_index == dynamic_frag_array->size) return;
    dynamic_frag_array->size--;
    // move every index after the index
    memmove(&dynamic_frag_array->element_buffer[index_of_index], &dynamic_frag_array->element_buffer[index_of_index + 1], (dynamic_frag_array->size - index_of_index) * sizeof(size_t));
    // set index state to default
    dynamic_frag_array->boolean_buffer[index] = false;
}

void* np_dynamic_frag_array_get(np_dynamic_frag_array* dynamic_frag_array, size_t index) {
    if (index >= dynamic_frag_array->buffer_size || !dynamic_frag_array->boolean_buffer[index]) return NULL;
    return (unsigned char*)dynamic_frag_array->data_buffer + index * dynamic_frag_array->type_size;
}

size_t np_dynamic_frag_array_get_index(np_dynamic_frag_array* dynamic_frag_array, size_t index) {
    if (index >= dynamic_frag_array->size) return dynamic_frag_array->size;
    return dynamic_frag_array->element_buffer[index];
}

size_t np_dynamic_frag_array_get_size(np_dynamic_frag_array* dynamic_frag_array) {
    return dynamic_frag_array->size;
}

void np_dynamic_frag_array_resize(np_dynamic_frag_array* dynamic_frag_array, size_t new_size) {
    // realloc data buffer
    dynamic_frag_array->data_buffer = realloc(dynamic_frag_array->data_buffer, dynamic_frag_array->type_size * new_size);
    np_assert(dynamic_frag_array->data_buffer != NULL, "dynamic_frag_array realloc error");
    // realloc element buffer
    dynamic_frag_array->element_buffer = realloc(dynamic_frag_array->element_buffer, sizeof(size_t) * new_size);
    np_assert(dynamic_frag_array->element_buffer != NULL, "dynamic_frag_array realloc error");
    // realloc boolean buffer
    dynamic_frag_array->boolean_buffer = realloc(dynamic_frag_array->boolean_buffer, sizeof(bool) * new_size);
    np_assert(dynamic_frag_array->boolean_buffer != NULL, "dynamic_frag_array realloc error");
    // set new boolean buffer region to false
    memset(&dynamic_frag_array->boolean_buffer[dynamic_frag_array->buffer_size], false, sizeof(bool) * (new_size - dynamic_frag_array->buffer_size));
    // set new buffer size
    dynamic_frag_array->buffer_size = new_size;
}

// private functions

size_t np_dynamic_frag_array_find_avalible_index(bool* boolean_array, size_t size) {
    // find avalible id by looping in the boolean array
    for (size_t index = 0; index < size; index++) if (!boolean_array[index]) return index;
    // if not found then return the id out of range
    return size;
}

size_t np_dynamic_frag_array_find_value(size_t* element_array, size_t size, size_t value) {
    // check every value in array and if found return the index
    for (size_t index = 0; index < size; index++) if (element_array[index] == value) return index;
    // else return oit of range index
    return size;
}