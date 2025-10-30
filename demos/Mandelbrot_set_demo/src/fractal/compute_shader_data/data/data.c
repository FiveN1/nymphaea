#include"data.h"

void mbs_cs_data_create(mbs_cs_data* cs_data, fractal_camera* camera, int resolution_x, int resolution_y, int max_iteration_count) {
    mbs_cs_data_set_camera_data(cs_data, camera);
    mbs_cs_data_set_resolution_data(cs_data, resolution_x, resolution_y);
    mbs_cs_data_set_iteration_data(cs_data, max_iteration_count);
}

void mbs_cs_data_set_camera_data(mbs_cs_data* cs_data, fractal_camera* camera) {
    cs_data->position_x = camera->position_x;
    cs_data->position_y = camera->position_y;
    cs_data->zoom = camera->zoom;
}

void mbs_cs_data_set_resolution_data(mbs_cs_data* cs_data, int resolution_x, int resolution_y) {
    cs_data->resolution_x = resolution_x;
    cs_data->resolution_y = resolution_y;
}

void mbs_cs_data_set_iteration_data(mbs_cs_data* cs_data, int max_iteration_count) {
    cs_data->max_iteration_count = max_iteration_count;
}