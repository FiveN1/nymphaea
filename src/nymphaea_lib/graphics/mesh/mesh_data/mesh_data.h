#ifndef NP_MESH_DATA
#define NP_MESH_DATA

#include<glad/glad.h>

// ## Mesh Data
// all arguments passed when creating a mesh packaged together into one struct.
// includes arrays with vertex, element and attribute data.
// NOTE: this data is only freed in 'np_mesh_create_procedural' function
typedef struct np_mesh_data {
    // verticies
    GLfloat* vertices;
    GLuint verticies_size;
    // indicies
    GLuint* indices;
    GLuint indices_size;
    // vertex attributes
    GLuint* attributes;
    GLuint attributes_size;
} np_mesh_data;

// create null / empty mesh data.
np_mesh_data np_mesh_data_empty();
// free allocated mesh data.
// - np_mesh_data mesh_data -> mesh data that will be freed.
void np_mesh_data_free(np_mesh_data mesh_data);

#endif NP_MESH_DATA