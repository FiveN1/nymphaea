#include"pch.h"
#include"mesh.h"

void np_mesh_create(np_mesh* mesh, np_mesh_data mesh_data) {
    np_mesh_create_advanced(mesh, mesh_data, GL_STATIC_DRAW, GL_STATIC_DRAW);
}

void np_mesh_create_procedural(np_mesh* mesh, np_mesh_data mesh_data) {
    np_mesh_create(mesh, mesh_data);
    // delete generated mesh_data
    np_mesh_data_free(mesh_data);
}

void np_mesh_create_advanced(np_mesh* mesh, np_mesh_data mesh_data, GLenum vertex_usage, GLenum element_usage) {
    // create vao (this has to be first)
    np_vao_create(&mesh->vao);
    np_vao_bind(mesh->vao);
    // set verticies array (vbo)
    np_vbo_create(&mesh->vbo, mesh_data.vertices, mesh_data.verticies_size, vertex_usage);
    np_vbo_bind(mesh->vbo);
    // set indicies array (ebo)
    np_ebo_create(&mesh->ebo, mesh_data.indices, mesh_data.indices_size, element_usage);
    np_ebo_bind(mesh->ebo);
    // set vertex (vao) attributes
    np_vao_set_attributes(mesh_data.attributes, mesh_data.attributes_size);
    // set number of indicies in the mesh
    mesh->element_size = mesh_data.indices_size / sizeof(GLuint);
    // unbind objects
    np_vao_unbind();
    np_vbo_unbind();
    np_ebo_unbind();
    // no shader
    mesh->shader_program = 0;
    // set default draw data & draw callback
    mesh->draw_data = NULL;
    mesh->draw_callback = &np_mesh_default_draw_callback;
    // debug
    #ifdef NP_DEBUG_MESH
    np_debug_print_green("np_mesh: created mesh at: %p", mesh);
    #endif
}

void np_mesh_delete(np_mesh* mesh) {
    // delete vertex & element arrays
    np_vbo_delete(&mesh->vbo);
    np_vao_delete(&mesh->vao);
    np_ebo_delete(&mesh->ebo);
    // reset the other variables
    mesh->element_size = 0;
    // set shader program id to 0
    mesh->shader_program = 0;
    // set all pointers to default
    free(mesh->draw_data);
    mesh->draw_data = NULL;
    mesh->draw_callback = &np_mesh_default_draw_callback;
    // debug
    #ifdef NP_DEBUG_MESH
    np_debug_print_yellow("np_mesh: deleted mesh at: %p", mesh);
    #endif
}

void np_mesh_draw(np_mesh* mesh) {
    np_mesh_draw_advanced(mesh, GL_TRIANGLES, mesh->element_size, 0);
}

void np_mesh_draw_advanced(np_mesh* mesh, GLenum mode, GLsizei size, const void* offset) {
    // bind mesh vao
    np_vao_bind(mesh->vao);
    // draw the mesh by indicies
    glDrawElements(mode, size, GL_UNSIGNED_INT, offset);
    np_vao_unbind();
}

void np_mesh_call_draw(np_mesh* mesh) {
    if (mesh->draw_callback != NULL) mesh->draw_callback(mesh, mesh->shader_program, mesh->draw_data);
}

void np_mesh_set_shader_program(np_mesh* mesh, np_shader_program shader_program) {
    mesh->shader_program = shader_program;
}

void np_mesh_set_draw_callback(np_mesh* mesh, void(*draw_callback)(struct np_mesh*, np_shader_program, void*)) {
    mesh->draw_callback = draw_callback;
}

void* np_mesh_set_draw_data(np_mesh* mesh, size_t data_size) {
    // create shader data copy on the heap 
    mesh->draw_data = realloc(mesh->draw_data, data_size);
    // check if allocation succeeded.
    np_assert(mesh->draw_data != NULL, "np_mesh: draw data allocation error");
    return mesh->draw_data;
}

void* np_mesh_get_draw_data(np_mesh* mesh) {
    return mesh->draw_data;
}

void np_mesh_default_draw_callback(np_mesh* mesh, np_shader_program shader_program, void* shader_data) {
    // set current shader program
    np_shader_program_use(shader_program);
    // draw mesh
    np_mesh_draw(mesh);
}