#ifndef MANDELBROT_SET_DEMO_COLOR_SCHEME_H
#define MANDELBROT_SET_DEMO_COLOR_SCHEME_H

typedef struct color_rgb {
    float r;
    float g;
    float b;
} color_rgb;


color_rgb hex_to_rgb(int hex_value);



#endif MANDELBROT_SET_DEMO_COLOR_SCHEME_H