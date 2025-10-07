#include"pch.h"
#include"ebo.h"

void np_ebo_create(np_ebo* ebo, GLuint* indices, GLuint size, GLenum usage) {
    // generate the index buffer
    glGenBuffers(1, ebo);
    // set ebo data (indicies data) by binding, setting & unbinding this array
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, *ebo);
    // set the actual data
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, indices, usage);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void np_ebo_delete(np_ebo* ebo) {
    glDeleteBuffers(1, ebo);
}

void np_ebo_create_buffer(np_ebo ebo, GLuint* indices, GLuint size, GLenum usage) {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, indices, usage);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void np_ebo_set_data(np_ebo ebo, GLuint* indices, GLuint offset, GLsizeiptr size) {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, offset, size, indices);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void np_ebo_bind(np_ebo ebo) {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
}

void np_ebo_unbind() {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}