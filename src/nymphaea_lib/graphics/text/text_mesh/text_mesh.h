#ifndef NP_TEXT_MESH_H
#define NP_TEXT_MESH_H

#include"nymphaea_lib/graphics/mesh/mesh.h"
#include"nymphaea_lib/graphics/font/font.h"
#include"nymphaea_lib/core/data_structures/array/array.h"

// mesh textu

typedef struct np_text_mesh {
    // mesh of the text
    np_mesh* mesh;
    // to achive fast update speeds, mesh data needs to change as little as possible. (avoiding malloc / realloc)
    np_mesh_data mesh_data;
    

} np_text_mesh;

void np_text_mesh_create(np_text_mesh* text_mesh, np_mesh* empty_mesh);

void np_text_mesh_delete(np_text_mesh* text_mesh);

void np_text_mesh_generate(np_text_mesh* text_mesh, np_font* font, char* string, size_t string_len);

/*
* Změny:
*
* [29.10.2025]
* vytvořeno, z důvodu abstrakce, text meshe a text outline. 
* také začištění kodů v text.c
*
*
*/

#endif NP_TEXT_MESH_H