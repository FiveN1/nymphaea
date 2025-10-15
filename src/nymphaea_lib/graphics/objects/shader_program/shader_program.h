#ifndef NP_SHAPDER_PROGRAM_H
#define NP_SHAPDER_PROGRAM_H

#include<glad/glad.h>

/*
* ## Shader Program
* 
* A pipline of shaders that draw & color the triangles on your screen.
* Every mesh geometry is shaded in using this pipeline
*
* Shader Program is set by an id (unsigned int)
*/
typedef GLuint np_shader_program; // id?

// create shader program
np_shader_program np_shader_program_create(const GLchar* vertex_shader_source, const GLchar* geometry_shader_source, const GLchar* fragment_shader_source);
// create shader program form source code stored in files
// ADD FILE CHECK !!
np_shader_program np_shader_program_load(const char* vertex_shader_filename, const char* geometry_shader_filename, const char* fragment_shader_filename);
// delete the shader program
void np_shader_program_delete(np_shader_program* shader_program);
// set shader program as current
void np_shader_program_use(np_shader_program shader_program);

// UBO vs SSBO
// https://stackoverflow.com/questions/33589784/ssbo-as-bigger-ubo

// Frustum culling

/*
* Změny
*
* [...]
* [10.06.2025] přidána podpora geometry shaderu
* - není to hezké alo co
*
*
*/

#endif NP_SHAPDER_PROGRAM_H