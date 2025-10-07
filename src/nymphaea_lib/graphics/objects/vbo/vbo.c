#include"pch.h"
#include"vbo.h"

void np_vbo_create(np_vbo* vbo, GLfloat* vertices, GLuint size, GLenum usage) {
    // generate the vertex buffer
    glGenBuffers(1, vbo);
    // set vbo data (verticies data) by binding, setting & unbinding this array
    glBindBuffer(GL_ARRAY_BUFFER, *vbo);
    // set the actual data
    glBufferData(GL_ARRAY_BUFFER, size, vertices, usage);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void np_vbo_create_buffer(np_vbo vbo, GLfloat* vertices, GLuint size, GLenum usage) {
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, size, vertices, usage);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}
void np_vbo_set_data(np_vbo vbo, GLfloat* vertices, GLuint offset, GLsizeiptr size) {
    // doc pg.269
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferSubData(GL_ARRAY_BUFFER, offset, size, vertices);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void np_vbo_delete(np_vbo* vbo) {
    glDeleteBuffers(1, vbo);
}

void np_vbo_bind(np_vbo vbo) {
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
}

void np_vbo_unbind() {
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}
