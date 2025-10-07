#include"pch.h"
#include"mesh_mia_system.h"
#include"nymphaea_lib/graphics/mesh/mesh.h"

void np_mia_sys_mesh_draw_all(np_mia_registry* mesh_registry) {
    //np_log("...");
    // NOTE: meshes are drawn in reverse. meaning the latest mesh is drawn first
    size_t size = 0;
    if (np_mia_registry_get_size(mesh_registry) != 0) size = np_mia_registry_get_size(mesh_registry) - 1;
    for (size_t i = 0; i < np_mia_registry_get_size(mesh_registry); i++) {
        //np_log("i: %llu, size: %llu", i, size);
        np_mesh* mesh = (np_mesh*)np_mia_get_by_id(mesh_registry, size - i);
        np_mesh_call_draw(mesh);
    }
}

void np_mia_sys_mesh_draw_all_one_shader(np_mia_registry* mesh_registry, np_shader_program* shader) {
    np_shader_program_use(*shader);
    for (size_t i = 0; i < np_mia_registry_get_size(mesh_registry); i++) {
        //np_mesh* mesh = (np_mesh*)np_mia_get_by_id(mesh_registry, i);
        //np_mesh_draw_unshaded(mesh);
    }
}

void np_mia_sys_mesh_delete(np_mia_registry* mesh_registry) {
    for (size_t i = 0; i < np_mia_registry_get_size(mesh_registry); i++) {
        //np_mesh* mesh = (np_mesh*)np_mia_get_by_id(mesh_registry, i);
        //np_mesh_draw(mesh);
    }
}