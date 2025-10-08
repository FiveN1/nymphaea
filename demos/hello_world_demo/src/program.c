#include"program.h"

// set program data
void program_create(program_data* program) {
    // program will run by default
    program->is_running = true;

    // initilize the renderer (GLFW)
    np_renderer_create();

    // create window
    np_window_create(&program->window, program, 800, 800, "Hello world!");
    np_window_bind_event_callback(&program->window, &program_on_event); // also bind the window callback so we can close the window!

    // create GUI
    np_gui_create(&program->gui_context);
    np_gui_enable(&program->gui_context, NP_GUI_TEXT, 8);

    // add text
    np_gui_text_create(&program->gui_context, "Hello World!");
}

// iterate on program data
void program_run(program_data* program) {
    // main loop
    while(program->is_running) {

        // update (draw) GUI
        np_gui_update(&program->gui_context, &program->window);

        // update window
        np_window_update(&program->window);
    }

}

// free program data
void program_free(program_data* program) {
    // free GUI data
    np_gui_delete(&program->gui_context);

    // free window data
    np_window_delete(&program->window);

    // delete renderer
    np_renderer_delete();
}

// process program data on event
void program_on_event(np_event event, void* data) {
    // cast input data to program
    program_data* program = (program_data*)data;

    // close window
    if (event.type == NP_WINDOW_CLOSE_EVENT) {
        program->is_running = false;
        np_window_close(&program->window);
    }
}