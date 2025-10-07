#ifndef NP_FRAMEBUFFER_H
#define NP_FRAMEBUFFER_H

#include"nymphaea_lib/graphics/objects/fbo/fbo.h"
#include"nymphaea_lib/graphics/objects/rbo/rbo.h"

#include"nymphaea_lib/graphics/objects/texture_2d/texture_2d.h"

typedef struct np_framebuffer {
    np_fbo fbo;
    np_rbo rbo;
    np_texture_2d texture;
} np_framebuffer;

// create a framebuffer
void np_framebuffer_create(np_framebuffer* framebuffer, GLsizei width, GLsizei height);
// delete framebuffer data
void np_framebuffer_delete(np_framebuffer* framebuffer);
// bind framebuffer
// each draw call after this will then be drawn to the framebuffer texture
void np_framebuffer_bind(np_framebuffer* framebuffer);
// unbind framebuffer
// any new draw calls will not appear on the texture after this
void np_framebuffer_unbind();
// get the texture id on wich the frame will be drawn
np_texture_2d np_framebuffer_get_texture(np_framebuffer* framebuffer);


// přidat update framebuffer s novým rozlišením

#endif NP_FRAMEBUFFER_H