#ifndef HASH_TABLE_H
#define HASH_TABLE_H

// https://www.youtube.com/watch?v=knV86FlSXJ8

// Search: O(1) - konstantní (nezvěčuje se s množstvím v poli)
// Sapce: O(N) - Zvěčuje se s množstvím klíčů

// Prakticky stejné jako dictionary
/*
*
*
*
*
*
*
* UPDATE:
* - 07.08.2024 vytvořeno & implementace
*
*/


typedef struct {
    void* value_buffer;
    const char** key_buffer; // Musí to být pro check když dojde ke kolizi
    size_t buff_size;
    size_t size;
    size_t type_size;
} hash_table;


void hashtCreate(hash_table* instance, size_t size, size_t type_size);

void hashtDelete(hash_table* instance);

size_t hashtAdd(hash_table* instance, const char* key, const void* data);

size_t hashtLocate(hash_table* instance, const char* key);

void* hashtGet(hash_table* instance, size_t index);

// array : data [15165, 51516, 5165165, ...]
// data[hash(string)]

// array : ["key1", "key2", "apple", ...]
// state : [000000, 001000, 001001, ...]
// (1) index určuje pořadí přidání klíčů
/*



*/



#endif HASH_TABLE_H