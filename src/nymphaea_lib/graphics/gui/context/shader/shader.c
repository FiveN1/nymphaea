#include"pch.h"
#include"shader.h"

void np_gui_color_shader_use(np_mesh* mesh, np_shader_program shader_program, np_gui_color_shader_data* data) {
    np_shader_program_use(shader_program);

    glUniform4f(glGetUniformLocation(shader_program, "color"), data->color[0], data->color[1], data->color[2], data->color[3]);
    // set uniforms
    glUniformMatrix3fv(glGetUniformLocation(shader_program, "model_matrix"), 1, GL_FALSE, np_transform_2d_get(data->text_transform)[0][0]);
    glUniformMatrix3fv(glGetUniformLocation(shader_program, "view_matrix"), 1, GL_FALSE, np_transform_2d_get(&data->camera_2d->transform)[0][0]);
    glUniformMatrix4fv(glGetUniformLocation(shader_program, "proj_matrix"), 1, GL_FALSE, np_camera_2d_get_matrix(data->camera_2d)[0][0]);
    np_mesh_draw(mesh);
}

void np_gui_text_shader_use(np_mesh* mesh, np_shader_program shader_program, np_gui_text_shader_data* data) {
    glEnable(GL_BLEND);
    glDisable(GL_DEPTH_TEST);

    np_shader_program_use(shader_program);
    // bind text atlas to shader
    np_texture_2d_bind_sampler_unit(data->font_atlas, shader_program, 0, "glyph");
    // set uniforms
    glUniformMatrix3fv(glGetUniformLocation(shader_program, "model_matrix"), 1, GL_FALSE, np_transform_2d_get(data->text_transform)[0][0]);
    glUniformMatrix3fv(glGetUniformLocation(shader_program, "view_matrix"), 1, GL_FALSE, np_transform_2d_get(&data->camera_2d->transform)[0][0]);
    glUniformMatrix4fv(glGetUniformLocation(shader_program, "proj_matrix"), 1, GL_FALSE, np_camera_2d_get_matrix(data->camera_2d)[0][0]);
    np_mesh_draw(mesh);

    glDisable(GL_BLEND);
    glEnable(GL_DEPTH_TEST);
}