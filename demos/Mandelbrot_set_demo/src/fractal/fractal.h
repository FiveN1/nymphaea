#ifndef MANDELBROT_SET_DEMO_FRACTAL_H
#define MANDELBROT_SET_DEMO_FRACTAL_H

#include<nymphaea_lib/graphics/graphics.h>

#include"compute_shader_data/data/data.h"
#include"compute_shader_data/color_scheme/color_scheme.h"


typedef struct fractal {
    np_compute_program compute_program;

    //int resolution_x;
    //int resolution_y;
    // general data
    mbs_cs_data data;
    np_ssbo data_ssbo;
    // color scheme data
    fractal_color_scheme_data color_scheme_data;
    np_ssbo color_scheme_data_ssbo;

} fractal;

void fractal_create(fractal* fractal_instance, fractal_camera* fractal_camera, int view_texture_width, int view_texture_height);

void fractal_update_camera_data(fractal* fractal_instance, fractal_camera* fractal_camera);

void fractal_update_viewport_data(fractal* fractal_instance, int view_texture_width, int view_texture_height);

// render fractal to texture
void fractal_render(fractal* fractal_instance, np_dsa_texture_2d view_texture, int view_texture_width, int view_texture_height);

#endif MANDELBROT_SET_DEMO_FRACTAL_H