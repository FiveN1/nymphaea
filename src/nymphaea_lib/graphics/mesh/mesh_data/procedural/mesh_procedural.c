#include"pch.h"
#include"mesh_procedural.h"

np_mesh_data np_mesh_procedural_rectangle(float width, float height) {
    np_mesh_data mesh_buffer_data;
    // verticies
    mesh_buffer_data.verticies_size = 4 * 2 * (GLuint)sizeof(GLfloat);
    mesh_buffer_data.vertices = (GLfloat*)malloc(mesh_buffer_data.verticies_size);
    mesh_buffer_data.vertices[0] = 0.0;    // bottom left
    mesh_buffer_data.vertices[1] = -height;
    mesh_buffer_data.vertices[2] = 0.0;    // top left
    mesh_buffer_data.vertices[3] = 0.0;
    mesh_buffer_data.vertices[4] = width;      // top right
    mesh_buffer_data.vertices[5] = 0.0;
    mesh_buffer_data.vertices[6] = width;      // bottom right
    mesh_buffer_data.vertices[7] = -height;
    // indicies
    mesh_buffer_data.indices_size = 6 * (GLuint)sizeof(GLuint);
    mesh_buffer_data.indices = (GLuint*)malloc(mesh_buffer_data.indices_size);
    mesh_buffer_data.indices[0] = 0;
    mesh_buffer_data.indices[1] = 1;
    mesh_buffer_data.indices[2] = 2;
    mesh_buffer_data.indices[3] = 2;
    mesh_buffer_data.indices[4] = 3;
    mesh_buffer_data.indices[5] = 0;
    // attributes
    mesh_buffer_data.attributes_size = 1 * (GLuint)sizeof(GLuint);
    mesh_buffer_data.attributes = (GLuint*)malloc(mesh_buffer_data.attributes_size);
    mesh_buffer_data.attributes[0] = 2;
    // return
    return mesh_buffer_data;
}

np_mesh_data np_mesh_procedural_rectangle_line(float width, float height) {
    np_mesh_data mesh_buffer_data;
    // verticies
    mesh_buffer_data.verticies_size = 4 * 2 * (GLuint)sizeof(GLfloat);
    mesh_buffer_data.vertices = (GLfloat*)malloc(mesh_buffer_data.verticies_size);
    mesh_buffer_data.vertices[0] = 0.0;    // bottom left
    mesh_buffer_data.vertices[1] = -height;
    mesh_buffer_data.vertices[2] = 0.0;    // top left
    mesh_buffer_data.vertices[3] = 0.0;
    mesh_buffer_data.vertices[4] = width;      // top right
    mesh_buffer_data.vertices[5] = 0.0;
    mesh_buffer_data.vertices[6] = width;      // bottom right
    mesh_buffer_data.vertices[7] = -height;
    // indicies
    mesh_buffer_data.indices_size = 8 * (GLuint)sizeof(GLuint);
    mesh_buffer_data.indices = (GLuint*)malloc(mesh_buffer_data.indices_size);
    mesh_buffer_data.indices[0] = 0;
    mesh_buffer_data.indices[1] = 1;
    mesh_buffer_data.indices[2] = 1;
    mesh_buffer_data.indices[3] = 2;
    mesh_buffer_data.indices[4] = 2;
    mesh_buffer_data.indices[5] = 3;
    mesh_buffer_data.indices[6] = 3;
    mesh_buffer_data.indices[7] = 0;
    // attributes
    mesh_buffer_data.attributes_size = 1 * (GLuint)sizeof(GLuint);
    mesh_buffer_data.attributes = (GLuint*)malloc(mesh_buffer_data.attributes_size);
    mesh_buffer_data.attributes[0] = 2;
    // return
    return mesh_buffer_data;
}


np_mesh_data np_mesh_procedural_pyramid(float a, float height) {
    // nejdříve vytvoříme data na stacku

    GLfloat vertices[] = {
        -a * 0.5f, 0.0f,  a * 0.5f, 0.83f, 0.70f, 0.44f, 0.0f, 0.0f,
        -a * 0.5f, 0.0f, -a * 0.5f, 0.83f, 0.70f, 0.44f, 1.0f, 0.0f,
         a * 0.5f, 0.0f, -a * 0.5f, 0.83f, 0.70f, 0.44f, 0.0f, 0.0f,
         a * 0.5f, 0.0f,  a * 0.5f, 0.83f, 0.70f, 0.44f, 1.0f, 0.0f,
         a * 0.0f, height,  a * 0.0f, 0.92f, 0.86f, 0.76f, 0.5f, 1.4f
    };
    GLuint indices[] = {
        2, 1, 0, // zakladna
        3, 2, 0, // zakladna
        0, 1, 4,
        1, 2, 4,
        2, 3, 4,
        3, 0, 4
    };
    GLuint attributes[] = {
        3, 3, 2
    };

    // Zkopírujeme na heap pro další použití

    np_mesh_data mesh_buffer_data;
    // vertices
    mesh_buffer_data.verticies_size = 8 * 5 * (GLuint)sizeof(GLfloat);
    mesh_buffer_data.vertices = (GLfloat*)malloc(mesh_buffer_data.verticies_size);
    memcpy(mesh_buffer_data.vertices, vertices, mesh_buffer_data.verticies_size);
    // indeices
    mesh_buffer_data.indices_size = 3 * 6 * (GLuint)sizeof(GLuint);
    mesh_buffer_data.indices = (GLuint*)malloc(mesh_buffer_data.indices_size);
    memcpy(mesh_buffer_data.indices, indices, mesh_buffer_data.indices_size);
    // attributes
    mesh_buffer_data.attributes_size = 3 * (GLuint)sizeof(GLuint);
    mesh_buffer_data.attributes = (GLuint*)malloc(mesh_buffer_data.attributes_size);
    memcpy(mesh_buffer_data.attributes, attributes, mesh_buffer_data.attributes_size);

    return mesh_buffer_data;
}