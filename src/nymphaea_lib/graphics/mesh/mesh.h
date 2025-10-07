#ifndef NP_MESH_H
#define NP_MESH_H
// functions and data structures used by mesh
#include"nymphaea_lib/graphics/objects/vbo/vbo.h"
#include"nymphaea_lib/graphics/objects/ebo/ebo.h"
#include"nymphaea_lib/graphics/objects/vao/vao.h"
#include"nymphaea_lib/graphics/program/shader_program/shader_program.h"
// addtitonal includes related to mesh
#include"mesh_data/mesh_data.h"
#include"mesh_data/procedural/mesh_procedural.h"
#include"mesh_mia_system/mesh_mia_system.h"

#define NP_DEBUG_MESH

// mesh.h by FiveN

// ## Mesh
// mesh is a collention of verticies, with indicies that make vertex conections and attributes that make order of vertex data.
// mesh data is stored only on the graphics card. 
// mesh is only used for rendering by a shader program.
// core part of modern rendering.
typedef struct np_mesh {
    // OpenGL objects. vbo and ebo hold mesh data, and vao connects vbo and ebo together.
    np_vao vao;
    np_vbo vbo;
    np_ebo ebo;
    // element buffer (ebo) size.
    GLuint element_size;
    // shader program that will be used for shading the mesh.
    np_shader_program shader_program;
    // shader data used in the draw callback.
    void* draw_data;
    // pointer to custom function that will be called on draw. this function determines the whole mesh draw process.
    void(*draw_callback)(struct np_mesh*, np_shader_program, void*);
} np_mesh;

// create mesh instance.
// #### Parameters
// - np_mesh* mesh           -> mesh instance.
// - np_mesh_data mesh_data  -> pointers to vertices, indices and attributes packaged together in 'np_mesh_data' struct that will be used to copy its data to the GPU.
void np_mesh_create(np_mesh* mesh, np_mesh_data mesh_data);
// create mesh instance with procedural mesh generator function passed directly. passed data will be deleted in this function. 
// #### Parameters
// - np_mesh* mesh           -> mesh instance.
// - np_mesh_data mesh_data  -> pointers to vertices, indices and attributes packaged together in 'np_mesh_data' struct that will be used to copy its data to the GPU.
void np_mesh_create_procedural(np_mesh* mesh, np_mesh_data mesh_data);
// create mesh instance with less abstraction.
// #### Parameters
// - np_mesh* mesh          -> mesh instance.
// - np_mesh_data mesh_data -> pointers to vertices, indices and attributes packaged together in 'np_mesh_data' struct that will be used to copy its data to the GPU.
// - GLenum vertex_usage    -> tells OpenGL how often the vertex data will change. can be: GL_STATIC_DRAW, GL_DYNAMIC_DRAW or GL_STREAM_DRAW.
// - GLenum element_usage   -> tells OpenGL how often the element data will change. can be: GL_STATIC_DRAW, GL_DYNAMIC_DRAW or GL_STREAM_DRAW.
void np_mesh_create_advanced(np_mesh* mesh, np_mesh_data mesh_data, GLenum vertex_usage, GLenum element_usage);
// delete mesh data.
// #### Parameters
// - np_mesh* mesh -> mesh instance.
void np_mesh_delete(np_mesh* mesh);
// draw mesh.
// #### Parameters
// - np_mesh* mesh -> mesh instance.
void np_mesh_draw(np_mesh* mesh);
// draw mesh with less abstraction.
// #### Parameters
// - np_mesh* mesh      -> mesh instance.
// - GLenum mode        -> draw mode. can be: GL_TRIANGLES, GL_LINES or GL_POINTS.
// - GLsizei size       -> size of element (index) array.
// - const void* offset -> offset in element (index) array.
void np_mesh_draw_advanced(np_mesh* mesh, GLenum mode, GLsizei size, const void* offset);
// draw mesh with the draw callback called.
// #### Parameters
// - np_mesh* mesh -> mesh instance.
void np_mesh_call_draw(np_mesh* mesh);
// set mesh shader
// #### Parameters
// - np_mesh* mesh -> mesh instance.
// - np_shader_program shader_program -> shader program instance used for rendering a mesh.
void np_mesh_set_shader_program(np_mesh* mesh, np_shader_program shader_program);
// set on draw callback
// #### Parameters
// - np_mesh* mesh -> mesh instance.
// - void(*draw_callback)(np_shader_program, np_mesh_buffers, void*) -> pointer to a function called on draw. all mesh draw code will be in this function.
void np_mesh_set_draw_callback(np_mesh* mesh, void(*draw_callback)(struct np_mesh*, np_shader_program, void*));
// allocate memory for draw data. the pointer to allocated draw data will be returned.
// #### Parameters
// - returns void* to empty draw data structure, that will be used to set draw data.
// - np_mesh* mesh -> mesh instance.
// - size_t data_size -> size of draw data struct.
void* np_mesh_set_draw_data(np_mesh* mesh, size_t data_size);
// get pointer to allocated draw data.
// #### Parameters
// - returns void* to draw data structure used by mesh.
// - np_mesh* mesh -> mesh instance.
void* np_mesh_get_draw_data(np_mesh* mesh);

// NOT part* of mesh
// default mesh draw callback.
// - np_mesh* mesh                    -> mesh instance.
// - np_shader_program shader_program -> shader program used for shading in the mesh.
// - void* shader_data                -> shader data used by the shader program.
void np_mesh_default_draw_callback(np_mesh* mesh, np_shader_program shader_program, void* shader_data);

/*
* Změny
* [...]
* [07.06.2025] draw data se ted doopravdy smažou při delete()
* [26.06.2025] funkce np_mesh_set_shader přenmenována na np_mesh_set_shader_program, protože jsem sem přidal np_shader.
*/

#endif NP_MESH_H