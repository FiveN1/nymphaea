#include"viewport.h"

void fractal_viewport_create(fractal_viewport* viewport, np_mia_registry* mesh_registry, np_shader* texture_shader, int resolution_x, int resolution_y) {
    // create frame texture
    np_dsa_texture_2d_create_empty(&viewport->texture, resolution_x, resolution_y, GL_RGBA32F, GL_NEAREST, GL_CLAMP_TO_EDGE);

    viewport->texture_width = resolution_x;
    viewport->texture_height = resolution_y;

    // create frame mesh
    viewport->mesh = np_mia_alloc(mesh_registry);
    np_mesh_data rect_mesh_data = np_mesh_shape_rectangle(1.0f, 1.0f, NP_MESH_SHAPE_UV);
    np_mesh_create(viewport->mesh, rect_mesh_data);
    np_mesh_data_free(rect_mesh_data);
    // set shader
    np_shader_data* shader_data = np_mesh_set_shader(viewport->mesh, texture_shader);
    *(np_dsa_texture_2d*)np_shader_data_get(shader_data, "tex") = viewport->texture;
}

void fractal_viewport_delete(fractal_viewport* viewport) {
    np_dsa_texture_2d_delete(&viewport->texture);
    viewport->texture_width = 0;
    viewport->texture_height = 0;
    viewport->mesh = NULL;
}

void fractal_viewport_resize(fractal_viewport* viewport, int resolution_x, int resolution_y) {
    // dumb approach
    np_dsa_texture_2d_delete(&viewport->texture);
    np_dsa_texture_2d_create_empty(&viewport->texture, resolution_x, resolution_y, GL_RGBA32F, GL_NEAREST, GL_CLAMP_TO_EDGE);
    np_shader_data* shader_data = (np_shader_data*)np_mesh_get_draw_data(viewport->mesh);
    *(np_dsa_texture_2d*)np_shader_data_get(shader_data, "tex") = viewport->texture;
}