#ifndef PROGRAM_H
#define PROGRAM_H

#include<stdio.h>
#include<stdlib.h>
#include<stdint.h>
#include<stdbool.h>

#include<nymphaea_lib/graphics/window/window.h>
#include<nymphaea_lib/graphics/gui/gui.h>
#include<nymphaea_lib/graphics/camera/camera_3d/freecam/freecam.h>
#include<nymphaea_lib/graphics/scene/scene.h>
#include<nymphaea_lib/graphics/scene/model/model.h>
#include<nymphaea_lib/graphics/debug/delta_time.h>

// data of the program
typedef struct program_data {
    bool is_running;
    // window
    np_window window;
    // gui
    np_gui_context gui;
    np_gui_text* fps_text;
    // movable camera
    np_freecam freecam;
    // scene that handels the rendering of meshes
    np_scene scene;
    // model rendered in scene
    np_model model;
} program_data;

void program_create(program_data* program);

void program_run(program_data* program);

void program_delete(program_data* program);

void program_on_event(np_event event, program_data* program);

#endif PROGRAM_H