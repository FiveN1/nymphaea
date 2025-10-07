#include"pch.h"
#include"dynamic_array.h"

void np_dynamic_array_create(np_dynamic_array* dynamic_array, size_t type_size) {
    // set up data
    dynamic_array->data = malloc(0);
    dynamic_array->block_size = 0;
    dynamic_array->type_size = type_size;
    dynamic_array->size = 0;
}

void np_dynamic_array_delete(np_dynamic_array* dynamic_array) {
    free(dynamic_array->data);
    dynamic_array->data = NULL;
    dynamic_array->block_size = 0;
    dynamic_array->type_size = 0;
    dynamic_array->size = 0;
}

void* np_dynamic_array_add(np_dynamic_array* dynamic_array) {
    dynamic_array->size++;
    // if there is more data in the array then allocated, the whole block will be reallocated with a bigger size.
    // NOTE: each time the buffer is reallocated it is enlargened only by 1.
    if (dynamic_array->size > dynamic_array->block_size) np_dynamic_array_resize(dynamic_array, dynamic_array->size);
    // return pointer to newly added memory so it can be set
    return (unsigned char*)dynamic_array->data + (dynamic_array->size - 1) * dynamic_array->type_size;
}

void np_dynamic_array_add_copy(np_dynamic_array* dynamic_array, const void* data) {
    dynamic_array->size++;
    // if there is more data in the array then allocated, the whole block will be reallocated with a bigger size.
    // NOTE: each time the buffer is reallocated it is enlargened only by 1.
    if (dynamic_array->size > dynamic_array->block_size) np_dynamic_array_resize(dynamic_array, dynamic_array->size);
    // copy the data into the array
    memcpy((unsigned char*)dynamic_array->data + (dynamic_array->size - 1) * dynamic_array->type_size, data, dynamic_array->type_size);
}

void np_dynamic_array_pop(np_dynamic_array* dynamic_array) {
    if (dynamic_array->size < 1) return;
    dynamic_array->size--;
}

void np_dynamic_array_insert(np_dynamic_array* dynamic_array, size_t index, const void* data) {
    // if larger than the current size, then add to the end.
    // this array cant have holes
    if (index > dynamic_array->size) index = dynamic_array->size;
    dynamic_array->size++;
    // reallocate if oweflown
    if (dynamic_array->size > dynamic_array->block_size) np_dynamic_array_resize(dynamic_array, dynamic_array->size);
    // shifts anything after insertion
    // NOTE: data that used to be at position 'index' will be shifted up
    memmove((unsigned char*)dynamic_array->data + (index + 1) * dynamic_array->type_size, (unsigned char*)dynamic_array->data + index * dynamic_array->type_size, (dynamic_array->size - index - 1) * dynamic_array->type_size);
    // copies data into now free position
    memcpy((unsigned char*)dynamic_array->data + index * dynamic_array->type_size, data, dynamic_array->type_size);
}

void np_dynamic_array_remove(np_dynamic_array* dynamic_array, size_t index) {
    // shifts whole buffer after index to index
    memmove((unsigned char*)dynamic_array->data + index * dynamic_array->type_size, (unsigned char*)dynamic_array->data + (index + 1) * dynamic_array->type_size, (dynamic_array->size - index) * dynamic_array->type_size);
    dynamic_array->size--;
}

void* np_dynamic_array_get(np_dynamic_array* dynamic_array, size_t index) {
    if (index >= dynamic_array->size) return NULL;
    return (unsigned char*)dynamic_array->data + index * dynamic_array->type_size;
}

size_t np_dynamic_array_get_size(np_dynamic_array* dynamic_array) {
    return dynamic_array->size;
}

void np_dynamic_array_resize(np_dynamic_array* dynamic_array, size_t new_size) {
    dynamic_array->data = realloc(dynamic_array->data, dynamic_array->type_size * new_size);
    np_assert(dynamic_array->data != NULL, "np_dynamic_array realloc error");
    dynamic_array->block_size = new_size;
}

void np_dynamic_array_clear(np_dynamic_array* dynamic_array) {
    dynamic_array->size = 0;
}