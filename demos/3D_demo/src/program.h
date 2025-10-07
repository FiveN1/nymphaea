#ifndef PROGRAM_H
#define PROGRAM_H

#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

#include<nymphaea_lib/graphics/graphics.h>

typedef struct program_data {
    bool is_running;
    np_window window;
    np_gui_context gui_context;
} program_data;

void program_create(program_data* program);

void program_run(program_data* program);

void program_free(program_data* program);

void program_on_event(np_event event, void* data);


#endif PROGRAM_H