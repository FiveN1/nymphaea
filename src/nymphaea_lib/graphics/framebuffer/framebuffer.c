#include"pch.h"
#include"framebuffer.h"

void np_framebuffer_create(np_framebuffer* framebuffer, GLsizei width, GLsizei height) {
    // create framebuffer
    framebuffer->fbo = np_fbo_create();
    np_fbo_bind(framebuffer->fbo);
    // create color texture
    np_texture_2d_create_empty(&framebuffer->texture, width, height, GL_RGB, GL_NEAREST, GL_CLAMP_TO_EDGE);
    // bind color texture to framebuffer
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, framebuffer->texture, 0);
    // create depth & stencil rbo texture for framebuffer
    framebuffer->rbo = np_rbo_create(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_DEPTH24_STENCIL8, width, height);
    // check fbo status
    np_fbo_check();
    np_fbo_unbind();
}

void np_framebuffer_delete(np_framebuffer* framebuffer) {
    np_rbo_delete(&framebuffer->rbo);
    np_texture_2d_delete(&framebuffer->texture);
    np_fbo_delete(&framebuffer->fbo);
}

void np_framebuffer_bind(np_framebuffer* framebuffer) {
    glBindFramebuffer(GL_FRAMEBUFFER, framebuffer->fbo);
}

void np_framebuffer_unbind() {
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

np_texture_2d np_framebuffer_get_texture(np_framebuffer* framebuffer) {
    return framebuffer->texture;
}