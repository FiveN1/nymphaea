#include"pch.h"
#include"id_array.h"

// this is the only one operation that is not O(1)
size_t find_avalible_id(bool* boolean_array, size_t size);
// find value in array
size_t find_value(size_t* id_array, size_t size, size_t value);

void np_id_array_create(np_id_array* id_array, size_t size, size_t type_size) {
    id_array->block = malloc(size * type_size);
    np_assert(id_array->block != NULL, "np_id_array malloc error");
    id_array->block_size = size;
    id_array->type_size = type_size;
    id_array->size = 0;
    id_array->id_block = (size_t*)malloc(sizeof(size_t) * size);
    np_assert(id_array->id_block != NULL, "np_id_array malloc error");
    id_array->boolean_block = (bool*)malloc(sizeof(bool) * size);
    np_assert(id_array->boolean_block != NULL, "np_id_array malloc error");
    for (size_t i = 0; i < size; i++) {
        id_array->boolean_block[i] = false;
        id_array->id_block[i] = 0;
    }
}

void np_id_array_delete(np_id_array* id_array) {
    free(id_array->block);
    id_array->block = NULL;
    id_array->block_size = 0;
    id_array->type_size = 0;
    id_array->size = 0;
    free(id_array->id_block);
    free(id_array->boolean_block);
}

size_t np_id_array_add(np_id_array* id_array, const void* data) {
    size_t id = find_avalible_id(id_array->boolean_block, id_array->block_size);
    // check if any avalible id found if not return the out of range one
    if (id == id_array->block_size) return id;
    // set data
    memcpy((unsigned char*)id_array->block + id * id_array->type_size, data, id_array->type_size);
    // update mem status
    id_array->boolean_block[id] = true;
    // update ids
    id_array->id_block[id_array->size] = id;
    id_array->size++;
    return id;
}

size_t np_id_array_add_empty(np_id_array* id_array) {
    size_t id = find_avalible_id(id_array->boolean_block, id_array->block_size);
    // check if any avalible id found if not return the out of range one
    if (id == id_array->block_size) return id;
    // set data
    memset((unsigned char*)id_array->block + id * id_array->type_size, 0, id_array->type_size);
    // update mem status
    id_array->boolean_block[id] = true;
    // update ids
    id_array->id_block[id_array->size] = id;
    id_array->size++;
    return id;
}

void np_id_array_remove(np_id_array* id_array, size_t id) {
    // update ids
    size_t id_of_id = find_value(id_array->id_block, id_array->size, id);
    if (id_of_id == id_array->size) return; // this ensures that the id is not out of range. because it was added with the add() function. and also that the id even exists so no need for a boolean check
    id_array->size--; // this has to be before memmove so it doesnt move memory from outside the block
    // move every id after the id being removed back by 1
    memmove(&id_array->id_block[id_of_id], &id_array->id_block[id_of_id + 1], (id_array->size - id_of_id) * sizeof(size_t));
    // update status array
    id_array->boolean_block[id] = false;
}

void* np_id_array_get(np_id_array* id_array, size_t id) {
    if (id >= id_array->block_size) return NULL;
    if (!id_array->boolean_block[id]) return NULL;
    return (unsigned char*)id_array->block + id * id_array->type_size;
}

size_t np_id_array_get_id_by_id(np_id_array* id_array, size_t id) {
    return id_array->id_block[id];
}

size_t np_id_array_get_id_by_ptr(np_id_array* id_array, const void* ptr) {
    // using pointer arithmetics to get the id. (ptr - base) / type_size
    return (size_t)((unsigned char*)ptr - (unsigned char*)id_array->block) / id_array->type_size;
}

size_t np_id_array_get_size(np_id_array* id_array) {
    return id_array->size;
}

size_t find_avalible_id(bool* boolean_array, size_t size) {
    // find avalible id by looping in the boolean array
    for (size_t id = 0; id < size; id++) if (!boolean_array[id]) return id;
    // if not found then return the id out of range
    return size;
}

size_t find_value(size_t* id_array, size_t size, size_t value) {
    // check every value in array and if found return the index
    for (size_t i = 0; i < size; i++) if (id_array[i] == value) return i;
    // else return oit of range index
    return size;
}