#ifndef NP_EBO_H
#define NP_EBO_H

#include<glad/glad.h>

// ## Element Buffer Object (EBO)
// EBO is just an array of indices. (uint array)
// each array is defined by an ID. (unsigned int)
typedef GLuint np_ebo;

// this functions creates the EBO and returns the ID of the EBO using glad.
// - np_ebo* ebo     -> ebo instance.
// - GLuint* indices -> pointer to array of indices.
// - GLuint size     -> size of array of indices.
// - GLenum usage    -> tells OpenGL how often this data will change. can be: GL_STATIC_DRAW, GL_DYNAMIC_DRAW or GL_STREAM_DRAW.
void np_ebo_create(np_ebo* ebo, GLuint* indices, GLuint size, GLenum usage);
// delete ebo.
// - np_ebo* ebo -> ebo instance.
void np_ebo_delete(np_ebo* ebo);
// allocates new element buffer on the gpu for this ebo. the old one is deallocated.
// - np_ebo ebo      -> ebo instance.
// - GLuint* indices -> pointer to array of indices.
// - GLuint size     -> size of array of indices.
// - GLenum usage    -> tells OpenGL how often this data will change. can be: GL_STATIC_DRAW, GL_DYNAMIC_DRAW or GL_STREAM_DRAW.
void np_ebo_create_buffer(np_ebo ebo, GLuint* indices, GLuint size, GLenum usage);
// change ebo data.
// - np_ebo ebo      -> ebo instance.
// - GLuint* indices -> pointer to array of indices.
// - GLuint offset   -> offset in current ebo where the new indices will be copied.
// - GLsizeiptr size -> size of array of indices copied.
void np_ebo_set_data(np_ebo ebo, GLuint* indices, GLuint offset, GLsizeiptr size);
// set instance of ebo as current.
// - np_ebo ebo -> ebo instance.
void np_ebo_bind(np_ebo ebo);
// unbind ebo.
void np_ebo_unbind();

#endif NP_EBO_H