#include"program.h"

void program_create(program_data* program) {
    np_log_sucess("created program");


    program->is_running = true;

    np_renderer_create();

    np_window_create(&program->window, program, 800, 800, "3D_demo");
    np_window_bind_event_callback(&program->window, &program_on_event);


    np_gui_create(&program->gui_context);
    np_gui_enable(&program->gui_context, NP_GUI_TEXT, 8);

    np_gui_text* text1 = np_gui_text_create(&program->gui_context, "in dev");

}

void program_run(program_data* program) {

    while(program->is_running) {

        np_gui_update(&program->gui_context, &program->window);
        
        np_window_update(&program->window);
    }

}

void program_free(program_data* program) {
    np_gui_delete(&program->gui_context);
    np_window_delete(&program->window);
    np_renderer_delete();
}

void program_on_event(np_event event, void* data) {
    program_data* program = (program_data*)data;

    // close window
    if (event.type == NP_WINDOW_CLOSE_EVENT) {
        np_debug_print("closing");
        program->is_running = false;
        np_window_close(&program->window);
    }
}