#include"pch.h"
#include"mia.h"

void np_mia_create(np_mia* mia, size_t registry_count) {
    // create MIA
    // - id array holding other id arrays that hold data
    np_id_array_create(mia, registry_count, sizeof(np_id_array));
}

void np_mia_delete(np_mia* mia) {
    // clear registries
    for (size_t i = 0; i < np_id_array_get_size(mia); i++) np_id_array_delete((np_id_array*)np_id_array_get(mia, np_id_array_get_id_by_id(mia, i)));
    // delete MIA
    np_id_array_delete(mia);
}

np_mia_registry* np_mia_registry_create(np_mia* mia, size_t size, size_t type_size) {
    // allocate space for registry
    np_mia_registry* registry = (np_id_array*)np_id_array_get(mia, np_id_array_add_empty(mia));
    // create registry in that empty space
    np_id_array_create(registry, size, type_size);
    return registry;
}

void np_mia_registry_delete(np_mia* mia, np_mia_registry* registry) {
    // delete any id array data like pointers ext..
    np_id_array_delete(registry);
    // remove from mia
    np_id_array_remove(mia, np_id_array_get_id_by_ptr(mia, registry));
    registry = NULL;
}

np_id_array* np_mia_registry_get(np_mia* mia, size_t registry) {
    return (np_id_array*)np_id_array_get(mia, registry);
}

size_t np_mia_registry_get_size(np_mia_registry* registry) {
    return np_id_array_get_size(registry);
}

void* np_mia_alloc(np_mia_registry* registry) {
    size_t id = np_id_array_add_empty(registry);
    np_assert(id != np_id_array_get_size(registry), "np_mia: registry at %p full", registry);
    return np_id_array_get(registry, id);
}

void np_mia_free(np_mia_registry* registry, void* data) {
    np_id_array_remove(registry, np_id_array_get_id_by_ptr(registry, data));
    // after deleting, the pointer shoud not point to an empty memory.
    data = NULL;
}

void* np_mia_get(np_mia_registry* registry, size_t id) {
    return np_id_array_get(registry, id);
}

void* np_mia_get_by_id(np_mia_registry* registry, size_t id) {
    return np_id_array_get(registry, np_id_array_get_id_by_id(registry, id));
}



//
// UNDER CONSTRUCTION
//

