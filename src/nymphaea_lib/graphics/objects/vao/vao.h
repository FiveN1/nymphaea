#ifndef NP_VAO_H
#define NP_VAO_H

#include<glad/glad.h>

// ## VAO (Vertex Array Object)
// VAO is an object that holds the attributes of the vertex array.
// so this means that the first attribute (the first 3 numbers) in each vertex are for example the vertex position.
// the next coud be something diffrent.
// each attribute is defined by its own ID.
// each VAO is defined by an ID. (GLuint)
typedef GLuint np_vao;

// this functions creates the VAO and returns the ID of the VAO using glad.
// - np_vao* vao -> vao instance.
void np_vao_create(np_vao* vao);
// delete vao.
// - np_vao* vao -> vao instance.
void np_vao_delete(np_vao* vao);
// set all of the attributes of a vertex from array.
// - GLuint* attributes     -> pointer to array of attributes. array of attributes holds sizes (GLuint) of each attribute in a vertex.
// - GLuint attributes_size -> size of array of attributes.
void np_vao_set_attributes(GLuint* attributes, GLuint attributes_size);
// set vao attribute of bound vbo, each attribute will be passed into the shader.
// - GLuint layout         -> attribute ID.
// - GLuint num_components -> amount of components (numbers) in attribute.
// - GLenum type           -> data type of attribute.
// - GLsizei stride        -> the total number of attributes (values) in vertex.
// - const void* offset    -> the attribute offset in stride.
void np_vao_set_attribute(GLuint layout, GLuint num_components, GLenum type, GLsizei stride, const void* offset);
// set instance of vao as current.
// - np_vao vao -> vao instance.
void np_vao_bind(np_vao vao);
// unbind vao.
void np_vao_unbind();

#endif NP_VAO_H