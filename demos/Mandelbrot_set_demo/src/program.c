#include"program.h"

// set program data
void program_create(program_data* program) {

    np_mia_create(&program->mia, 8);
    program->mesh_registry = np_mia_registry_create(&program->mia, 8, sizeof(np_mesh));

    // program will run by default
    program->is_running = true;
    program->render_gui = true;

    // initilize the renderer (GLFW)
    np_renderer_create();

    // create window
    np_window_create(&program->window, program, 1024, 768, "Mandelbrot set");
    np_window_bind_event_callback(&program->window, &program_on_event); // also bind the window callback so we can close the window!
    np_window_set_clear_color(0.0f, 0.0f, 0.0f, 1.0f);

    // texture shader
    np_shader_create_file(&program->texture_shader, "res/shaders/texture_shader/source.vert", "", "res/shaders/texture_shader/source.frag");
    np_shader_input_add_uniform(&program->texture_shader.shader_input, NP_UNIFORM_SAMPLER2D_DSA, "tex");

    fractal_camera_create(&program->fractal_camera_instance);
    fractal_create(&program->fractal_instance, &program->fractal_camera_instance, np_window_get_width(&program->window), np_window_get_height(&program->window));

    // GUI
    mbs_ui_create(&program->ui);

    // viewport
    fractal_viewport_create(&program->viewport, program->mesh_registry, &program->texture_shader, np_window_get_width(&program->window), np_window_get_height(&program->window));
    
}

// iterate on program data
void program_run(program_data* program) {

    double prev_time = np_delta_time_set_previous_time();

    double time_diffrence = 0.0;

    // main loop
    while(program->is_running) {
        // clear window
        np_window_clear_buffers();

        double delta_time = np_delta_time_get(&prev_time);

        // update and render fractal
        fractal_camera_update(&program->fractal_camera_instance, &program->window, delta_time);
        fractal_update_camera_data(&program->fractal_instance, &program->fractal_camera_instance);
        fractal_render(&program->fractal_instance, program->viewport.texture, program->viewport.texture_width, program->viewport.texture_height);
        
        // draw all meshes
        np_mia_sys_mesh_draw_all(program->mesh_registry);

        //
        // GUI
        //
        
        time_diffrence += delta_time;
        if (time_diffrence > 25.0) { // update every 25ms
            // set camera stats text
            char camera_stats_buffer[256];
            sprintf_s(camera_stats_buffer, sizeof(camera_stats_buffer), "position xy: (%lf, %lf) zoom: %lf", program->fractal_camera_instance.position_x, program->fractal_camera_instance.position_y, program->fractal_camera_instance.zoom);
            np_text_set(np_gui_text_get_text(program->ui.camera_stats), camera_stats_buffer);

            // set program stats text
            char program_stats_buffer[256];
            sprintf_s(program_stats_buffer, sizeof(program_stats_buffer), "ms: %lf fps: %u", delta_time, np_delta_time_to_fps(delta_time));
            np_text_set(np_gui_text_get_text(program->ui.program_stats), program_stats_buffer);
            
            char fractal_stats_buffer[256];
            sprintf_s(fractal_stats_buffer, sizeof(fractal_stats_buffer), "fractal type: Mandelbrot set; max iteration count: %i", program->fractal_instance.data.max_iteration_count);
            np_text_set(np_gui_text_get_text(program->ui.fractal_stats), fractal_stats_buffer);
            
            time_diffrence = 0.0;
        }
        
        // update (draw) GUI
        if (program->render_gui) np_gui_update(&program->ui.gui_context, &program->window);

        // update window
        np_window_update(&program->window);
    }
}

// free program data
void program_free(program_data* program) {
    // free GUI data
    mbs_ui_delete(&program->ui);

    // free window data
    np_window_delete(&program->window);

    // delete renderer
    np_renderer_delete();
}

// process program data on event
void program_on_event(np_event event, void* data) {
    // cast input data to program
    program_data* program = (program_data*)data;

    if (event.type == NP_WINDOW_RESIZE_EVENT) {
        // update texture
        //fractal_viewport_resize(&program->viewport, np_window_get_width(&program->window), np_window_get_height(&program->window));
        //fractal_update_viewport_data(&program->viewport, np_window_get_width(&program->window), np_window_get_height(&program->window));
    }


    // close window
    if (event.type == NP_WINDOW_CLOSE_EVENT) {
        program->is_running = false;
        np_window_close(&program->window);
    }
}