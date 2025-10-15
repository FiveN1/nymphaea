#ifndef NP_TEXTURE_2D_H
#define NP_TEXTURE_2D_H

#include<glad/glad.h>

#include"nymphaea_lib/graphics/objects/shader_program/shader_program.h"

//#define NP_DEBUG_TEXTURE_2D

/*
* ## Texture 2D
* A two-dimensional array of pixels stored on the GPU.
*
* ### Related functions
* - np_texture_2d_create_from_file
* - np_texture_2d_create
* - np_texture_2d_create_empty
* - np_texture_2d_delete
* - np_texture_2d_generate_mipmap
* - np_texture_2d_bind_sampler_unit
* - np_texture_2d_bind
* - np_texture_2d_unbind
* - np_texture_2d_set_pixels
*/
typedef GLuint np_texture_2d;

// create texture 2D from an image file
// #### Parameters
// - np_texture_2d* texture_2d -> texture_2d instance
// - GLenum format -> format or amount of color channels a texture will have (GL_RGBA, GL_RGB, GL_RG, GL_R)
// - GLenum filter -> how a texture will be displayed. pixelated or blobby (GL_NEAREST, GL_LINEAR)
// - GLenum wrap -> how a texture will be wrapped over a mesh. repeated or clamped...
void np_texture_2d_create_from_file(np_texture_2d* texture_2d, GLenum format, GLenum filter, GLenum wrap, const char* filename);
// create texture 2D
void np_texture_2d_create(np_texture_2d* texture_2d, GLsizei width, GLsizei height, GLenum format, GLenum filter, GLenum wrap, GLenum pixles_format, const void* pixels);
// create an empty texture by allocating an empty buffer on the CPU and copying it to the GPU. for better performence use the newer 'np_dsa_texture_2d'!
void np_texture_2d_create_empty(np_texture_2d* texture_2d, GLsizei width, GLsizei height, GLenum format, GLenum filter, GLenum wrap);
// delete texture 2D data
void np_texture_2d_delete(np_texture_2d* texture_2d);
// generate mipmaps for texture 2D
void np_texture_2d_generate_mipmap(np_texture_2d* texture_2d);
// bind texture 2D and sampler unit
void np_texture_2d_bind_sampler_unit(np_texture_2d texture_2d, np_shader_program shader_program, GLuint unit, const char* uniform_name);
// set instance of texture 2D as current
void np_texture_2d_bind(np_texture_2d texture_2d);
// unbind texture 2D
void np_texture_2d_unbind();
// set texture pixels at location with size
void np_texture_2d_set_pixels(np_texture_2d texture_2d, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, const void* pixels);


/*
* Změny
*
* [30.05.2025] vylepšeny komentáře funkcí
* [10.06.2025] uprava unit při np_texture_2d_bind_sampler_unit() ted stačí zadat pouze číslo.
*
*
*
*
*/

#endif NP_TEXTURE_2D_H