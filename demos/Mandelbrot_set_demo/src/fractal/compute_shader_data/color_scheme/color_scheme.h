#ifndef MANDELBROT_SET_DEMO_COLOR_SCHEME_H
#define MANDELBROT_SET_DEMO_COLOR_SCHEME_H

#include<nymphaea_lib/graphics/graphics.h>

typedef struct color_rgb {
    float r;
    float g;
    float b;
} color_rgb;

color_rgb hex_to_rgb(int hex_value);

typedef struct fractal_color_scheme_data {
    int color_count;
    color_rgb colors[10];
} fractal_color_scheme_data;

void fractal_color_scheme_data_create(fractal_color_scheme_data* fractal_color_scheme_data_instance);


#endif MANDELBROT_SET_DEMO_COLOR_SCHEME_H