#ifndef MANDELBROT_SET_DEMO_PROGRAM_H
#define MANDELBROT_SET_DEMO_PROGRAM_H

#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

#include<nymphaea_lib/graphics/graphics.h>

// data of this demo program
typedef struct program_data {
    bool is_running;
    np_window window;
    np_gui_context gui_context;
} program_data;

// set program data
void program_create(program_data* program);

// iterate on program data
void program_run(program_data* program);

// free program data
void program_free(program_data* program);

// process program data on event
void program_on_event(np_event event, void* data);

#endif MANDELBROT_SET_DEMO_PROGRAM_H