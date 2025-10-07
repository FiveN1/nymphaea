#include"pch.h"
#include"rbo.h"

np_rbo np_rbo_create(GLenum target, GLenum attachment, GLenum format, GLsizei width, GLsizei height) {
    // generate rbo
    np_rbo rbo;
    glGenRenderbuffers(1, &rbo);
    // bind
    glBindRenderbuffer(GL_RENDERBUFFER, rbo);
    // set rbo data (image)
    glRenderbufferStorage(GL_RENDERBUFFER, format, width, height);
    // link fbo with rbo
    glFramebufferRenderbuffer(target, attachment, GL_RENDERBUFFER, rbo);
    glBindRenderbuffer(GL_RENDERBUFFER, 0);
    // return id
    return rbo;
}

void np_rbo_delete(np_rbo* rbo) {
    glDeleteRenderbuffers(1, rbo);
}

void np_rbo_bind(np_rbo rbo) {
    glBindRenderbuffer(GL_RENDERBUFFER, rbo);
}

void np_rbo_unbind() {
    glBindRenderbuffer(GL_RENDERBUFFER, 0);
}