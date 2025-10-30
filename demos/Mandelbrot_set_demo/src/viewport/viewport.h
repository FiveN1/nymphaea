#ifndef MANDELBROT_SET_DEMO_FRAME_H
#define MANDELBROT_SET_DEMO_FRAME_H

#include<nymphaea_lib/graphics/graphics.h>

// Frame
//
// frame shader, that shades the whole viewport with a texture.
//
typedef struct fractal_viewport {
    np_dsa_texture_2d texture;    
    int texture_width;
    int texture_height;

    np_mesh* mesh;
} fractal_viewport;


void fractal_viewport_create(fractal_viewport* viewport, np_mia_registry* mesh_registry, np_shader* texture_shader, int resolution_x, int resolution_y);

void fractal_viewport_delete(fractal_viewport* viewport);

void fractal_viewport_resize(fractal_viewport* viewport, int resolution_x, int resolution_y);

// TODO:
// spravit texture system !! (HOTOVO :))
// dodělat mesh shape system (HOTOVO)
// pass shader jako texture shader (HOTOVO)
// přidat transform a kameru

#endif MANDELBROT_SET_DEMO_FRAME_H