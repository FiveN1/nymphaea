#ifndef MANDELBROT_SET_DEMO_UI_H
#define MANDELBROT_SET_DEMO_UI_H

#include<nymphaea_lib/graphics/graphics.h>

typedef struct mbs_ui {
    np_gui_context gui_context;
    np_gui_text* program_stats;
    np_gui_text* camera_stats;
    np_gui_text* fractal_stats;

} mbs_ui;

void mbs_ui_create(mbs_ui* ui);

void mbs_ui_delete(mbs_ui* ui);

#endif MANDELBROT_SET_DEMO_UI_H