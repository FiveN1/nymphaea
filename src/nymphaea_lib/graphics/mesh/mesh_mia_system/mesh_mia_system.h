#ifndef NP_MESH_MIA_SYSTEM_H
#define NP_MESH_MIA_SYSTEM_H

#include"nymphaea_lib/core/mia/mia.h"
#include"nymphaea_lib/graphics/objects/shader_program/shader_program.h"

/*
* Mesh MIA Systems
*
* Diffrent systems tahat iterate over every mesh in a MIA registry
*
*/

// draw all meshes in registry
void np_mia_sys_mesh_draw_all(np_mia_registry* mesh_registry);
// draw all meshes in registry with the same shader
void np_mia_sys_mesh_draw_all_one_shader(np_mia_registry* mesh_registry, np_shader_program* shader);
// delete all meshes in registry
void np_mia_sys_mesh_delete(np_mia_registry* mesh_registry);


// Only call draw callbacks??

#endif NP_MESH_MIA_SYSTEM_H