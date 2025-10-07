#ifndef NP_FBO_H
#define NP_FBO_H

#include<glad/glad.h>

/*
* Framebuffer
*
* A framebuffer is an object holding the pixel data about the frame.
*
*/
typedef GLuint np_fbo;
// create new fbo
np_fbo np_fbo_create();
// delete fbo data
void np_fbo_delete(np_fbo* fbo);
// bind fbo
void np_fbo_bind(np_fbo fbo);
// unbind fbo
void np_fbo_unbind();
// check fbo status
void np_fbo_check();

#endif NP_FBO_H