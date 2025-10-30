#include"fractal.h"

void fractal_create(fractal* fractal_instance, fractal_camera* fractal_camera, int view_texture_width, int view_texture_height) {

    np_compute_program_load(&fractal_instance->compute_program, "res/shaders/compute/source2.comp");

    // general data
    mbs_cs_data_create(&fractal_instance->data, fractal_camera, view_texture_width, view_texture_height, 100);
    np_ssbo_create(&fractal_instance->data_ssbo, sizeof(mbs_cs_data), &fractal_instance->data, GL_STREAM_DRAW, 1);
    
    // color scheme data
    fractal_color_scheme_data_create(&fractal_instance->color_scheme_data);
    np_ssbo_create(&(fractal_instance->color_scheme_data_ssbo), sizeof(fractal_color_scheme_data), &fractal_instance->color_scheme_data, GL_STATIC_DRAW, 2);

}

void fractal_update_camera_data(fractal* fractal_instance, fractal_camera* fractal_camera) {
    // update data
    mbs_cs_data_set_camera_data(&fractal_instance->data, fractal_camera);
}

void fractal_update_viewport_data(fractal* fractal_instance, int view_texture_width, int view_texture_height) {
    fractal_instance->data.resolution_x = view_texture_width;
    fractal_instance->data.resolution_y = view_texture_height;
}


void fractal_render(fractal* fractal_instance, np_dsa_texture_2d view_texture, int view_texture_width, int view_texture_height) {
    // send general data ssbo
    // is updated every frame
    np_ssbo_set_data(fractal_instance->data_ssbo, &fractal_instance->data, 0, sizeof(mbs_cs_data));
    // calculate fractal
    np_dsa_texture_2d_bind_layout_unit(view_texture, 0, GL_WRITE_ONLY, GL_RGBA32F); // stačí jen jednou?
    np_compute_program_use(fractal_instance->compute_program, ceil(view_texture_width / 8), ceil(view_texture_height / 4), 1);
}