#include"pch.h"
#include"hash_table.h"

// hashne string na číslo
size_t hash(const char* string);
// najde první volný index
size_t findEmptyIndex(hash_table* instance);
// najde index klíče
size_t findKeyIndex(hash_table* instance, const char* key);

void hashtCreate(hash_table* instance, size_t size, size_t type_size) {
    instance->value_buffer = malloc(type_size * size);
    instance->key_buffer = malloc(sizeof(*instance->key_buffer) * size);
    instance->buff_size = size;
    instance->size = 0;
    instance->type_size = type_size;

    for (size_t i = 0; i < instance->buff_size; i++) {
        instance->key_buffer[i] = NULL;
    }
}

void hashtDelete(hash_table* instance) {
    free(instance->value_buffer);
    free(instance->key_buffer);
    instance->value_buffer = NULL;
    instance->key_buffer = NULL;
    instance->buff_size = 0;
    instance->size = 0;
}

size_t hashtAdd(hash_table* instance, const char* key, const void* data) {
    if (instance->size >= instance->buff_size) return 0;    // check if full
    size_t index = hash(key) % instance->buff_size;         // vytvoří hash id
    if (instance->key_buffer[index])                        // collision check
        index = findEmptyIndex(instance);                   // pokud je index zabraný najde se jiný
    instance->key_buffer[index] = key;
    instance->size++;
    memcpy((unsigned char*)instance->value_buffer + index * instance->type_size, data, instance->type_size);
    return index;
}

size_t hashtLocate(hash_table* instance, const char* key) {
    size_t index = hash(key) % instance->buff_size;
    if (!instance->key_buffer[index] || strcmp(instance->key_buffer[index], key)) // check jestli string je stejný 
        index = findKeyIndex(instance, key);
    return index;
}

void* hashtGet(hash_table* instance, size_t index) {
    if (index > instance->buff_size) return NULL;
    if (!instance->key_buffer[index]) return NULL;
    return (unsigned char*)instance->value_buffer + index * instance->type_size;
}


size_t hash(const char* string) {
    // credit: http://www.cse.yorku.ca/~oz/hash.html
    unsigned long hash = 5381;
    int c;
    while (c = *string++)
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
    return hash;
}

size_t findEmptyIndex(hash_table* instance) {
    for (size_t i = 0; i < instance->size; i++)
        if (!instance->key_buffer[i]) return i;
    np_log_error("ERROR: hash table full!");
    np_log_error("file: %s line: %d", __FILE__, __LINE__);
    return 0;
}

size_t findKeyIndex(hash_table* instance, const char* key) {
    for (size_t i = 0; i < instance->buff_size; i++) {
        if (instance->key_buffer[i]) {
            if (!strcmp(instance->key_buffer[i], key)) 
                return i;
        }
    }
    np_log_error("ERROR: key: \'%s\' not found!", key);
    np_log_error("file: %s line: %d", __FILE__, __LINE__);
    return 0;
}