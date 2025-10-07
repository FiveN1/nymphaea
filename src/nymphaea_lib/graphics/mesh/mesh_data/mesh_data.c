#include"pch.h"
#include"mesh_data.h"

np_mesh_data np_mesh_data_empty() {
    np_mesh_data mesh_data = {NULL, 0, NULL, 0, NULL, 0};
    return mesh_data;
}

void np_mesh_data_free(np_mesh_data mesh_data) {
    free(mesh_data.vertices);
    mesh_data.vertices = NULL;
    free(mesh_data.indices);
    mesh_data.indices = NULL;
    free(mesh_data.attributes);
    mesh_data.attributes = NULL;
}