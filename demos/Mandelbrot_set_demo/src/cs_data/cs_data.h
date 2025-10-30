#ifndef MANDELBROT_SET_DEMO_CS_DATA_H
#define MANDELBROT_SET_DEMO_CS_DATA_H

#include"camera/camera.h"

// data sent to compute shader
// NOTE: this struct must be same in the compute shader !!
typedef struct mbs_cs_data {
    //
    double position_x;
    double position_y;
    double zoom;
    //
    int resolution_x;
    int resolution_y;
    //
    int max_iteration_count;
} mbs_cs_data;

void mbs_cs_data_create(mbs_cs_data* cs_data, mbs_camera* camera, int resolution_x, int resolution_y, int max_iteration_count);

void mbs_cs_data_set_camera_data(mbs_cs_data* cs_data, mbs_camera* camera);

void mbs_cs_data_set_resolution_data(mbs_cs_data* cs_data, int width, int height);

void mbs_cs_data_set_iteration_data(mbs_cs_data* cs_data, int max_iteration_count);

#endif MANDELBROT_SET_DEMO_CS_DATA_H