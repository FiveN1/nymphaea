#include"program.h"

void program_create(program_data* program) {
    // program will run by default
    program->is_running = true;

    // renderer
    np_renderer_create();

    // window 4:3
    np_window_create(&program->window, program, 800, 600, "3D demo");
    np_window_set_clear_color(0.0f, 0.2f, 0.0f, 1.0f); // green background
    np_window_bind_event_callback(&program->window, &program_on_event);
    np_window_set_vsync(true); // capped at maximum screen refresh rate

    // camera
    np_freecam_create(&program->freecam);

    // gui
    np_gui_create(&program->gui);
    np_gui_enable(&program->gui, NP_GUI_TEXT, 8);

    // create gui text at top left corner
    program->fps_text = np_gui_text_create(&program->gui, "delta time: 0ms, fps: 0");
    np_transform_2d_set_position(np_gui_text_get_transform(program->fps_text), (vec2){-(4.0f / 3.0f), 1.0f});

    // scene
    np_scene_create(&program->scene);
    // set main camera
    program->scene.main_camera = np_freecam_get_camera(&program->freecam);

    // add point light
    
    // add directional light

    // add model to scene
    np_model_create(&program->scene, "res/models/garfield/scene.gltf");
}

void program_run(program_data* program) {
    // data for delta time
    double prev_time = np_delta_time_set_previous_time();

    // data for fps text
    double time_diffrence = 0.0;
    char buff[128];

    // main loop
    while (program->is_running) {
        // cleat window
        np_window_clear_buffers();

        // get delta time
        double delta_time = np_delta_time_get(&prev_time);

        time_diffrence += delta_time;
        if (time_diffrence > 25.0) { // update každých 25ms
            sprintf(buff, "delta time: %lfms, fps: %u", delta_time, np_delta_time_to_fps(delta_time));
            np_text_set(np_gui_text_get_text(program->fps_text), buff);
            time_diffrence = 0.0;
        }
        // update camera
        np_freecam_update(&program->freecam, &program->window, 90.0f);
        
        // draw scene
        np_scene_draw(&program->scene);

        // update nymphaea gui
        np_gui_update(&program->gui, &program->window);

        // update window
        np_window_update(&program->window);
    }
}

void program_delete(program_data* program) {
    // delete gui
    np_gui_delete(&program->gui);

    // delete window befor renderer
    np_window_delete(&program->window);

    // delete renderer
    np_renderer_delete();
}

void program_on_event(np_event event, program_data* program) {

    // update freecam
    np_freecam_on_event(&program->freecam, event, &program->window);

    // on window close
    if (event.type == NP_WINDOW_CLOSE_EVENT) {
        program->is_running = false;
        np_window_close(&program->window);
    }
}