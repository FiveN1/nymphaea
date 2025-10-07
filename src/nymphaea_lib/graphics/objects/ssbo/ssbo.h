#ifndef NP_SSBO_H
#define NP_SSBO_H

#include<glad/glad.h>

/*
* ## Shader Storage Buffer Object (SSBO)
* Shader Storage Buffer Object is used for storing and retrieving data from within the GLSL
*
* ### Related Functions
* - np_ssbo_create
* - np_ssbo_delete
* - np_ssbo_bind
* - np_ssbo_bind_base
* - np_ssbo_unbind
*/
typedef GLuint np_ssbo;

void np_ssbo_create(np_ssbo* ssbo, GLsizeiptr size, const void* data, GLenum usage, GLuint index);

void np_ssbo_delete(np_ssbo* ssbo);

void np_ssbo_bind(np_ssbo ssbo);

void np_ssbo_bind_base(np_ssbo ssbo, GLuint index);

void np_ssbo_unbind();

#endif NP_SSBO_H