#include"ui.h"

void mbs_ui_create(mbs_ui* ui) {
    np_gui_create(&ui->gui_context);
    np_gui_enable(&ui->gui_context, NP_GUI_TEXT, 8);

    // add text
    np_gui_text* text1 = np_gui_text_create(&ui->gui_context, "Mandelbrot set demo");
    np_tr2_set_position(np_gui_text_get_transform(text1), (vec2){-1.0f, 1.0f});
    np_tr2_set_scale(np_gui_text_get_transform(text1), (vec2){1.5f, 1.5f});

    ui->program_stats = np_gui_text_create(&ui->gui_context, "ms: 0.0 fps: 0");
    np_tr2_set_position(np_gui_text_get_transform(ui->program_stats), (vec2){-1.0f, 0.93f});

    ui->camera_stats = np_gui_text_create(&ui->gui_context, "position xy: (0.0, 0.0) zoom: 0.0");
    np_tr2_set_position(np_gui_text_get_transform(ui->camera_stats), (vec2){-1.0f, 0.88f});

    ui->fractal_stats = np_gui_text_create(&ui->gui_context, "fractal type: Mandelbrot set; max iteration count: 0");
    np_tr2_set_position(np_gui_text_get_transform(ui->fractal_stats), (vec2){-1.0f, 0.83f});
}

void mbs_ui_delete(mbs_ui* ui) {
    // free GUI data
    np_gui_delete(&ui->gui_context);
}