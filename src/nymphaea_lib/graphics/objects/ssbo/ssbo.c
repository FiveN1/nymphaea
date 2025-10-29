#include"pch.h"
#include"ssbo.h"

void np_ssbo_create(np_ssbo* ssbo, GLsizeiptr size, const void* data, GLenum usage, GLuint index) {
    glGenBuffers(1, ssbo);
    np_ssbo_bind(*ssbo);
    glBufferData(GL_SHADER_STORAGE_BUFFER, size, data, usage);
    glBindBufferBase(GL_SHADER_STORAGE_BUFFER, index, *ssbo);
    np_ssbo_unbind();
}

void np_ssbo_delete(np_ssbo* ssbo) {
    glDeleteBuffers(1, ssbo);
    *ssbo = 0;
}

void np_ssbo_bind(np_ssbo ssbo) {
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, ssbo);
}

void np_ssbo_bind_base(np_ssbo ssbo, GLuint index) {
    glBindBufferBase(GL_SHADER_STORAGE_BUFFER, index, ssbo);
}

void np_ssbo_unbind() {
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);
}

void np_ssbo_set_data(np_ssbo ssbo, void* data, GLuint offset, GLsizeiptr size) {
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, ssbo);
    glBufferSubData(GL_SHADER_STORAGE_BUFFER, offset, size, data);
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);
}