#ifndef MANDELBROT_SET_DEMO_CAMERA_H 
#define MANDELBROT_SET_DEMO_CAMERA_H

#include<nymphaea_lib/graphics/graphics.h>

typedef struct mbs_camera {
    double position_x;
    double position_y;
    double zoom;

    //np_ssbo ssbo;
} mbs_camera;


void mbs_camera_create(mbs_camera* camera);

void mbs_camera_update(mbs_camera* camera, np_window* window, double delta_time);

void mbs_camera_on_event(mbs_camera* camera, np_event event, np_window* window);

#endif MANDELBROT_SET_DEMO_CAMERA_H