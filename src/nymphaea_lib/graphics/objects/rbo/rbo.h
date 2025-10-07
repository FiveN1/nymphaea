#ifndef NP_RBO_H
#define NP_RBO_H

#include<glad/glad.h>

/*
* Render Buffer Object
*
* Fast buffer hor holdinf data that you wont use in a shader.
*
*/
typedef GLuint np_rbo;

np_rbo np_rbo_create(GLenum target, GLenum attachment, GLenum format, GLsizei width, GLsizei height);

void np_rbo_delete(np_rbo* rbo);

void np_rbo_bind(np_rbo rbo);

void np_rbo_unbind();

#endif NP_RBO_H
