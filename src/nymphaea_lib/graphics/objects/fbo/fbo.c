#include"pch.h"
#include"fbo.h"

np_fbo np_fbo_create() {
    np_fbo fbo;
    glGenFramebuffers(1, &fbo);
    return fbo;
}

void np_fbo_delete(np_fbo* fbo) {
    glDeleteFramebuffers(1, fbo);
}

void np_fbo_bind(np_fbo fbo) {
    glBindFramebuffer(GL_FRAMEBUFFER, fbo);
}

void np_fbo_unbind() {
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void np_fbo_check() {
    GLenum status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
    np_assert(status == GL_FRAMEBUFFER_COMPLETE, "Framebuffer error: %u", status);
}