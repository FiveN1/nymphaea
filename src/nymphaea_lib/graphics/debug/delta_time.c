#include"pch.h"
#include"delta_time.h"

double np_delta_time_set_previous_time() {
    return np_get_time();
}

double np_delta_time_get(double* previous_time) {
    double current_time = np_get_time();
    double delta_time = current_time - *previous_time;
    *previous_time = current_time;
    return delta_time;
}

unsigned int np_delta_time_to_fps(double delta_time) {
    return (unsigned int)(1000.0 / delta_time);
}