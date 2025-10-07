#include"pch.h"
#include"vao.h"

void np_vao_create(np_vao* vao) {
    glGenVertexArrays(1, vao);
}

void np_vao_delete(np_vao* vao) {
    glDeleteVertexArrays(1, vao);
}

void np_vao_bind(np_vao vao) {
    glBindVertexArray(vao);
}

void np_vao_unbind() {
    glBindVertexArray(0);
}

void np_vao_set_attribute(GLuint layout, GLuint num_components, GLenum type, GLsizei stride, const void* offset) {
    glVertexAttribPointer(layout, num_components, type, GL_FALSE, stride, offset);
    glEnableVertexAttribArray(layout);
}

void np_vao_set_attributes(GLuint* attributes, GLuint attributes_size) {
    // get stride wich is the total number of attributes in array
    GLuint stride = 0;
    for (GLuint attrib = 0; attrib < attributes_size / sizeof(GLuint); attrib++) {
        stride += attributes[attrib];
    }
    // set attributes from array
    size_t offset = 0;
    for (GLuint attrib = 0; attrib < attributes_size / sizeof(GLuint); attrib++) {
        np_vao_set_attribute(attrib, attributes[attrib], GL_FLOAT, stride * sizeof(GLfloat), (GLvoid*)(offset * sizeof(GLfloat)));
        //np_log("atrib set: %u, %i, %llu, %llu", attrib, attributes[attrib], stride, (GLvoid*)(offset * sizeof(GLfloat)));
        offset += attributes[attrib];
    }



}

// TODO:
// add functionality to change vao data. if possible
// https://gamedev.stackexchange.com/questions/75989/what-is-the-correct-way-to-reset-and-load-new-data-into-gl-array-buffer
// glDisableVertexAttribArray();