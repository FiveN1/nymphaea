#ifndef NP_VBO_H
#define NP_VBO_H

#include<glad/glad.h>

// ## Vertex Buffer Object (VBO)
// VBO is just an array of verticies. (float array)
// each array is defined by an ID (unsigned int)
typedef GLuint np_vbo;

// this functions creates the VBO and returns the ID of the VBO using glad.
// - np_vbo* vbo       -> vbo instance.
// - GLfloat* vertices -> array of vertex data.
// - GLuint size       -> vertex array data size.
// - GLenum usage      -> tells OpenGL how often this data will change. can be: GL_STATIC_DRAW, GL_DYNAMIC_DRAW or GL_STREAM_DRAW.
void np_vbo_create(np_vbo* vbo, GLfloat* vertices, GLuint size, GLenum usage);
// delete vbo
// - np_vbo* vbo -> vbo instance.
void np_vbo_delete(np_vbo* vbo);
// allocates new vertex buffer on the gpu. the old one is deallocated
// - np_vbo vbo        -> vbo instance.
// - GLfloat* vertices -> array of vertex data.
// - GLuint size       -> vertex array data size.
// - GLenum usage      -> tells OpenGL how often this data will change. can be: GL_STATIC_DRAW, GL_DYNAMIC_DRAW or GL_STREAM_DRAW.
void np_vbo_create_buffer(np_vbo vbo, GLfloat* vertices, GLuint size, GLenum usage);
// change vbo data
// - np_vbo vbo        -> vbo instance.
// - GLfloat* vertices -> array of vertex data.
// - GLuint offset     -> offset in vao, where the new vertex data shall be copied.
// - GLsizeiptr size   -> size of copied vertex data array.
void np_vbo_set_data(np_vbo vbo, GLfloat* vertices, GLuint offset, GLsizeiptr size);
// set instance of vbo as current
// - np_vbo vbo -> vbo instance.
void np_vbo_bind(np_vbo vbo);
// unbind vbo
void np_vbo_unbind();

#endif NP_VBO_H