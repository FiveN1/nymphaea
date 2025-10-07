#ifndef NP_MESH_PROCEDURAL_H
#define NP_MESH_PROCEDURAL_H

#include"nymphaea_lib/graphics/mesh/mesh_data/mesh_data.h"

// Procedural Mesh Generator Functions
// - all functions return 'np_mesh_data' -> arrays of data compacted into one structure.
// - NOTE: theese functions allocate large chunks of memory when used! use them as little as possible!
// - theese arrays do need to be freed after used to create a mesh. the only function they are freed in is 'np_mesh_create_procedural'.

// generate mesh rectangle of 'width' and 'height'
// #### Parameters
// - float width  -> width of generated rectangle. (in units)
// - float height -> height of generated rectangle. (in units)
// #### Note
// use with np_mesh_create_procedural()
np_mesh_data np_mesh_procedural_rectangle(float width, float height);
// generate mesh rectangle for line rendering of 'width' and 'height'
// #### Parameters
// - float width  -> width of generated rectangle. (in units)
// - float height -> height of generated rectangle. (in units)
// #### Note
// use with np_mesh_create_procedural()
np_mesh_data np_mesh_procedural_rectangle_line(float width, float height);

// attributes:
// - vec3 positon
// - vec3 color
// - vec2 uv
np_mesh_data np_mesh_procedural_pyramid(float a, float height);

/*
* Změny
* [31.05.2025] Vylepšeny poznámky
* [13.06.2025] upraven postup malování základny pyramidy aby byl CCW.
* 
*
*
***/


#endif NP_MESH_PROCEDURAL_H