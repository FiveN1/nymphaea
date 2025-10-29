#include"pch.h"
#include"shader.h"

void np_shader_create_file(np_shader* shader, const char* vs_filename, const char* gs_filename, const char* fs_filename) {
    shader->shader_program = np_shader_program_load(vs_filename, gs_filename, fs_filename);
    np_shader_input_create(&shader->shader_input);
}

void np_shader_create_source(np_shader* shader, const char* vs, const char* gs, const char* fs) {
    shader->shader_program = np_shader_program_create(vs, gs, fs);
    np_shader_input_create(&shader->shader_input);
}

void np_shader_delete(np_shader* shader) {
    np_shader_program_delete(&shader->shader_program);
    np_shader_input_delete(&shader->shader_input);
}

np_shader_data* np_mesh_set_shader(np_mesh* mesh, np_shader* shader) {
    np_mesh_set_shader_program(mesh, shader->shader_program);
    np_mesh_set_draw_callback(mesh, &np_shader_data_draw_callback);
    np_shader_data* shader_data = np_mesh_set_draw_data(mesh, sizeof(np_shader_data));
    np_shader_data_create(shader_data, &shader->shader_input);
    return shader_data;
}