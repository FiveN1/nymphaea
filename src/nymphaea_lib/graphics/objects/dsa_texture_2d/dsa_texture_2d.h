#ifndef NP_DSA_TEXTURE_2D_H
#define NP_DSA_TEXTURE_2D_H

#include<glad/glad.h>

#include"nymphaea_lib/graphics/objects/shader_program/shader_program.h"

#define NP_DEBUG_DSA_TEXTURE_2D

/*
* ## Direct State Access Texture 2D
* Direct State Access (DSA) Texture 2D uses less bind calls and is therefore slightly faster.
* 
* ### Supported versions
* Is supported from OpenGL version 4.6
*
* ### Related Functions
* - np_dsa_texture_2d_create_from_file
* - np_dsa_texture_2d_create
* - np_dsa_texture_2d_create_empty
* - np_dsa_texture_2d_generate_mipmap
* - np_dsa_texture_2d_bind_sampler_unit
* - np_dsa_texture_2d_bind_layout_unit
*
*/
typedef GLuint np_dsa_texture_2d;

// create DSA texture 2D from a stored image
void np_dsa_texture_2d_create_from_file(np_dsa_texture_2d* dsa_texture_2d, GLenum format, GLenum filter, GLenum wrap, const char* filename);
// create DSA texture 2D
void np_dsa_texture_2d_create(np_dsa_texture_2d* dsa_texture_2d, GLuint width, GLuint height, GLenum format, GLenum filter, GLenum wrap, GLenum pixels_format, const void* pixels);
// create an empty DSA texture 2D
void np_dsa_texture_2d_create_empty(np_dsa_texture_2d* dsa_texture_2d, GLuint width, GLuint height, GLenum format, GLenum filter, GLenum wrap);
// delete DSA texture 2D (NOTE: MAY NOT WORK, NEED TEST)
void np_dsa_texture_2d_delete(np_dsa_texture_2d* dsa_texture_2d);
// generate mipmaps for DSA texture 2D
void np_dsa_texture_2d_generate_mipmap(np_dsa_texture_2d dsa_texture_2d);
// bind DSA texture 2D unit of a sampler
void np_dsa_texture_2d_bind_sampler_unit(np_dsa_texture_2d dsa_texture_2d, np_shader_program shader_program, GLuint unit, const char* uniform_name);
// bind DSA texture 2D unit of a layout. (mostly used in compute shaders)
void np_dsa_texture_2d_bind_layout_unit(np_dsa_texture_2d dsa_texture_2d, GLuint unit, GLenum access, GLenum format);

/*
* Změny:
*
* [...]
*
* [27.10.2025] 
* přidán filter a wrap do argumentů create funkcí. 
* spraveno filtrování textur.
*
*/

#endif NP_DSA_TEXTURE_2D_H
