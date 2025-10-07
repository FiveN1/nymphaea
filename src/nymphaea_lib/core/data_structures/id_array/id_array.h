#ifndef NP_ID_ARRAY_H
#define NP_ID_ARRAY_H

#include"pch.h"

// id_array.h by FiveN

/*
* ID Array (Indexed Array) RENAME TO FRAG ARRAY
*
* An id array keeps the ids of data in the array even after some other data were added or removed.
* An array where you can easily remove any data at any position without performence loss O(1)
* This is done by keeping track of the indices of the data being stored.
*
* ### Related Functions
* - np_id_array_create
* - np_id_array_delete
* - np_id_array_add
* - np_id_array_add_empty
* - np_id_array_remove
* - np_id_array_get
* - np_id_array_get_id_by_id
* - np_id_array_get_id_by_ptr
* - np_id_array_get_size
*/
typedef struct np_id_array {
    // this is where the data is stored
    void* block;
    // the size of the block
    size_t block_size;
    // size of the type in bytes being stored in the block
    size_t type_size;
    // block in wich the indicies are held
    size_t* id_block;
    // current size of the indicies in id_block
    size_t size;
    // to check if memory is occupied as fast as possible O(1)
    bool* boolean_block;
} np_id_array;

// create an id array
void np_id_array_create(np_id_array* id_array, size_t size, size_t type_size);
// delete id array data
void np_id_array_delete(np_id_array* id_array);
// add data to id array
size_t np_id_array_add(np_id_array* id_array, const void* data);
// add empty 'NULL' data to id array
size_t np_id_array_add_empty(np_id_array* id_array);
// remove data from array
void np_id_array_remove(np_id_array* id_array, size_t id);
// get data from id array
void* np_id_array_get(np_id_array* id_array, size_t id);
// get value of the id array at id so from (0 to size)
size_t np_id_array_get_id_by_id(np_id_array* id_array, size_t id);
// get id of data in array with a pointer to the data
size_t np_id_array_get_id_by_ptr(np_id_array* id_array, const void* ptr); // TOHO SE ZBAVIT ?
// get curren size of id array
size_t np_id_array_get_size(np_id_array* id_array);

// jméno frag_array by sedlo líp, v budoucnu možná změnit
// - frag jako že je fragmentovaný

#endif NP_ID_ARRAY_H