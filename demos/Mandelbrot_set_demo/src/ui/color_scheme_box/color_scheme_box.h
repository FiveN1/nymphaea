#ifndef MANDELBROT_SET_DEMO_COLOR_SCHEME_BOX_H
#define MANDELBROT_SET_DEMO_COLOR_SCHEME_BOX_H

#include<nymphaea_lib/graphics/graphics.h>

typedef struct mbs_color_scheme_box {
    np_mesh* mesh;
    np_dsa_texture_2d texture;
    // transform 2d


} mbs_color_scheme_box;

void mbs_color_scheme_box_create(mbs_color_scheme_box* color_scheme_box, np_mia_registry* mesh_registry, np_shader* texture_shader);


#endif MANDELBROT_SET_DEMO_COLOR_SCHEME_BOX_H