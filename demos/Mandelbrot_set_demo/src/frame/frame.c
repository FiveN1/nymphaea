#include"frame.h"

void mbs_frame_create(mbs_frame* frame, np_mia_registry* mesh_registry, np_shader* texture_shader, int resolution_x, int resolution_y) {

    // create frame texture
    np_dsa_texture_2d_create_empty(&frame->texture, resolution_x, resolution_y, GL_RGBA32F, GL_NEAREST, GL_CLAMP_TO_EDGE);
    
    np_tr2_create(&frame->transform);

    // create frame mesh
    frame->mesh = np_mia_alloc(mesh_registry);
    np_mesh_data rect_mesh_data = np_mesh_shape_rectangle(1.0f, 1.0f, NP_MESH_SHAPE_UV);
    np_mesh_create(frame->mesh, rect_mesh_data);
    np_mesh_data_free(rect_mesh_data);
    // set shader
    np_shader_data* shader_data = np_mesh_set_shader(frame->mesh, texture_shader);
    *(np_dsa_texture_2d*)np_shader_data_get(shader_data, "tex") = frame->texture;
}