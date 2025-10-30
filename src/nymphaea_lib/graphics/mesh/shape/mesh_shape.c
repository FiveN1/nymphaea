#include"pch.h"
#include"mesh_shape.h"

np_mesh_data np_mesh_shape_rectangle(float width, float height, enum np_mesh_shape_flags flags) {
    np_mesh_data mesh_data = {NULL, 0, NULL, 0, NULL, 0};

    // data pro kopírování (uloženo na stack pro tuto funkci)

    GLfloat vertices[] = { // position, uv, color
		-1.0f, -1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f,
		-1.0f,  1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
		 1.0f,  1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
		 1.0f, -1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f
	};

    GLuint indices[] = {
		0, 2, 1,
		0, 3, 2
	};

    // pro rect to jsou vždycky 4
    GLuint vertex_count = 4;
    // verticies size
    GLuint vertex_size = 2; // X, Y;
    // attrib count
    GLuint attributes_count = 1;

    // U, V;
    if (flags & NP_MESH_SHAPE_UV) {
        vertex_size += 2;
        attributes_count++;
    }
    // R, G, B;
    if (flags & NP_MESH_SHAPE_COLOR) {
        vertex_size += 3;
        attributes_count++;
    }

    //
    // vertices
    //

    // vertices alloc
    mesh_data.vertices_size = vertex_count * vertex_size * (GLuint)sizeof(GLfloat);
    mesh_data.vertices = (GLfloat*)malloc(mesh_data.vertices_size);

    // set data
    for (int vertex = 0; vertex < vertex_count; vertex++) {
        // position xyz
        mesh_data.vertices[vertex * vertex_size] = vertices[vertex * 7] * width;
        mesh_data.vertices[vertex * vertex_size + 1] = vertices[vertex * 7 + 1] * height;
        
        // texture uv
        if (flags & NP_MESH_SHAPE_UV) {
            mesh_data.vertices[vertex * vertex_size + 2] = vertices[vertex * 7 + 2];
            mesh_data.vertices[vertex * vertex_size + 3] = vertices[vertex * 7 + 3];
        } 
        
        // color
        if (flags & NP_MESH_SHAPE_COLOR) {
            mesh_data.vertices[vertex * vertex_size + 4] = vertices[vertex * 7 + 4];
            mesh_data.vertices[vertex * vertex_size + 5] = vertices[vertex * 7 + 5];
            mesh_data.vertices[vertex * vertex_size + 6] = vertices[vertex * 7 + 6];
        }
    }

    //
    // indicies
    //

    mesh_data.indices_size = 6 * (GLuint)sizeof(GLuint);
    mesh_data.indices = (GLuint*)malloc(mesh_data.indices_size);
    // indicies set data
    memcpy_s(mesh_data.indices, mesh_data.indices_size, indices, sizeof(indices));

    //
    // attributes
    //

    mesh_data.attributes_size = attributes_count * (GLuint)sizeof(GLuint);
    mesh_data.attributes = (GLuint*)malloc(mesh_data.attributes_size);

    // attributes set data
    mesh_data.attributes[0] = 2;
    if (flags & NP_MESH_SHAPE_UV) {
        mesh_data.attributes[1] = 2;
    }
    if (flags & NP_MESH_SHAPE_COLOR) {
        mesh_data.attributes[2] = 3;
    }

    // return
    return mesh_data;
}