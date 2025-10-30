#ifndef NP_MESH_SHAPE_H
#define NP_MESH_SHAPE_H

#include"nymphaea_lib/graphics/mesh/mesh_data/mesh_data.h"

/*
* mesh_shape.h
*
* includes functions for generating mesh shapes.
* NOTE: returned mesh data needs to be freed with the function 'np_mesh_data_free()'!
* 
*/

// flags for mesh generation.
// mesh attribute flags
enum np_mesh_shape_flags {
    // pozice je tu vždycky
    NP_MESH_SHAPE_UV = 1 << 0,
    NP_MESH_SHAPE_COLOR = 1 << 1
};

// generate mesh rectangle of 'width' and 'height'
// #### Parameters:
// - float width  -> width of generated rectangle. (in units)
// - float height -> height of generated rectangle. (in units)
// - enum np_mesh_shape_flags flags -> flags for mesh attributes.
// #### Return:
// - np_mesh_data -> mesh data struct with pointers ans sizes of mesh data arrays. NOTE: needs to be freed after passed into mesh!
np_mesh_data np_mesh_shape_rectangle(float width, float height, enum np_mesh_shape_flags flags);

/*
* Změny:
*
* [31.05.2025] 
* Vylepšeny poznámky
*
* [13.06.2025] 
* upraven postup malování základny pyramidy aby byl CCW.
* 
* [28.10.2025] 
* přejmenováno na np_mesh_shape
*
* [29.10.2025]
* plně implementována funkce 'np_mesh_shape_rectangle', s použitím flags a s vycentrováním na střed.
* + np_mesh_shape_flags
*
*/

#endif NP_MESH_SHAPE_H