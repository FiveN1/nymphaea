#ifndef MANDELBROT_SET_DEMO_PROGRAM_H
#define MANDELBROT_SET_DEMO_PROGRAM_H

#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

#include<nymphaea_lib/graphics/graphics.h>

#include"camera/camera.h"
#include"cs_data/cs_data.h"
#include"frame/frame.h"
#include"ui/ui.h"
#include"color_scheme/color_scheme.h"

// nějakej scene systém?
// - 2D scene system.
// 

// data of this demo program
typedef struct program_data {

    np_mia mia;
    np_mia_registry* mesh_registry;
    //np_mia_registry* dsa_texture_2d_registry;

    bool is_running;
    np_window window;

    np_shader texture_shader;

    // frame shader
    // použít np_rect
    // np_rect jde abstraktnout na np_mesh který je v gui s shaderem
    // jak by se to jmenovalo?
    // np_gui_shape?
    mbs_frame frame;

    // fractal view camera
    mbs_camera camera;

    // compute shader data
    int resolution_x;
    int resolution_y;
    np_compute_program compute_program;
    mbs_cs_data cs_data;
    np_ssbo cs_ssbo;


    np_ssbo color_ssbo;

    // gui
    mbs_ui ui;

} program_data;

// set program data
void program_create(program_data* program);

// iterate on program data
void program_run(program_data* program);

// free program data
void program_free(program_data* program);

// process program data on event
void program_on_event(np_event event, void* data);

/*
* TODO:
*
* Počítat fractal pouze pokud se něco změní.
* ukázat color scheme jako pruh někde dole v rohu
*
*
*/

#endif MANDELBROT_SET_DEMO_PROGRAM_H