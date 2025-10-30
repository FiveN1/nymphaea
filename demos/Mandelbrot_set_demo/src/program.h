#ifndef MANDELBROT_SET_DEMO_PROGRAM_H
#define MANDELBROT_SET_DEMO_PROGRAM_H

#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

#include<nymphaea_lib/graphics/graphics.h>

#include"fractal/fractal.h"
#include"fractal/camera/camera.h"
#include"viewport/viewport.h"
#include"ui/ui.h"



// data of this demo program
typedef struct program_data {
    // mia
    np_mia mia;
    np_mia_registry* mesh_registry;
    // window
    bool is_running;
    bool render_gui;
    np_window window;
    // texture shader for viewport
    np_shader texture_shader;
    // viewport that fills the whole screen
    fractal_viewport viewport;
    // fractal view camera
    fractal_camera fractal_camera_instance;
    // fractal calc system
    fractal fractal_instance;
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