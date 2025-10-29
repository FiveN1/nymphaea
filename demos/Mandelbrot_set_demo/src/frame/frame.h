#ifndef MANDELBROT_SET_DEMO_FRAME_H
#define MANDELBROT_SET_DEMO_FRAME_H

#include<nymphaea_lib/graphics/graphics.h>

// Frame
//
// frame shader, that shades the whole viewport with a texture.
//
typedef struct mbs_frame {
    np_dsa_texture_2d texture;    
    np_tr2 transform;
    np_mesh* mesh;

} mbs_frame;


// pass 2d_scene?

void mbs_frame_create(mbs_frame* frame, np_mia_registry* mesh_registry, np_shader* texture_shader, int resolution_x, int resolution_y);

// TODO:
// spravit texture system !! (HOTOVO :))
// dodělat mesh shape system (HOTOVO)
// pass shader jako texture shader (HOTOVO)
// přidat transform a kameru

#endif MANDELBROT_SET_DEMO_FRAME_H