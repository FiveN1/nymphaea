#ifndef MANDELBROT_SET_DEMO_CAMERA_H 
#define MANDELBROT_SET_DEMO_CAMERA_H

#include<nymphaea_lib/graphics/graphics.h>

typedef struct fractal_camera {
    double position_x;
    double position_y;
    double zoom;
} fractal_camera;


void fractal_camera_create(fractal_camera* camera);

void fractal_camera_update(fractal_camera* camera, np_window* window, double delta_time);

void fractal_camera_on_event(fractal_camera* camera, np_event event, np_window* window);

#endif MANDELBROT_SET_DEMO_CAMERA_H