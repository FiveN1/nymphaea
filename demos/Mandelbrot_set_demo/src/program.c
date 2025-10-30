#include"program.h"

// set program data
void program_create(program_data* program) {

    np_mia_create(&program->mia, 8);
    program->mesh_registry = np_mia_registry_create(&program->mia, 8, sizeof(np_mesh));

    // program will run by default
    program->is_running = true;

    // initilize the renderer (GLFW)
    np_renderer_create();

    // create window
    np_window_create(&program->window, program, 1024, 768, "Mandelbrot set");
    np_window_bind_event_callback(&program->window, &program_on_event); // also bind the window callback so we can close the window!
    np_window_set_clear_color(0.0f, 0.0f, 0.0f, 1.0f);

    // texture shader
    np_shader_create_file(&program->texture_shader, "res/shaders/texture_shader/source.vert", "", "res/shaders/texture_shader/source.frag");
    np_shader_input_add_uniform(&program->texture_shader.shader_input, NP_UNIFORM_SAMPLER2D_DSA, "tex");

    //
    // GUI
    //
    mbs_ui_create(&program->ui);
    
    //
    // Fractal
    //

    program->resolution_x = np_window_get_width(&program->window);
    program->resolution_y = np_window_get_height(&program->window);

    // frame
    mbs_frame_create(&program->frame, program->mesh_registry, &program->texture_shader, program->resolution_x, program->resolution_y);
    // compute 
    np_compute_program_load(&program->compute_program, "res/shaders/compute/source2.comp");

    mbs_camera_create(&program->camera, 1);    

    mbs_cs_data_create(&program->cs_data, &program->camera, program->resolution_x, program->resolution_y, 100);
    np_ssbo_create(&program->cs_ssbo, sizeof(mbs_cs_data), &program->cs_data, GL_STREAM_DRAW, 1);

    // lajolla
    color_rgb colors[] = {
		hex_to_rgb(0x1f1e0f),  
		hex_to_rgb(0x332312),  
		hex_to_rgb(0x5b2f22),  
        hex_to_rgb(0x91403c), 
        hex_to_rgb(0xc94e4a), 
        hex_to_rgb(0xe1714d),
        hex_to_rgb(0xe8914f),
        hex_to_rgb(0xefb553),
        hex_to_rgb(0xf7dd79),
        hex_to_rgb(0xfcf9cb)
	};
    int color_count = (int)(sizeof(colors) / sizeof(color_rgb));
    
    // send data to gpu
    size_t copy_buffer_size = sizeof(color_count) + sizeof(colors);
    void* copy_buffer = malloc(copy_buffer_size);
    memcpy_s(copy_buffer, copy_buffer_size, &color_count, sizeof(color_count));
    memcpy_s((unsigned char*)copy_buffer + sizeof(color_count), copy_buffer_size - sizeof(color_count), &colors, sizeof(colors));
    np_ssbo_create(&program->color_ssbo, copy_buffer_size, copy_buffer, GL_STATIC_DRAW, 2);
    free(copy_buffer);

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

        // update camera
        mbs_camera_update(&program->camera, &program->window, delta_time);

        // update data
        mbs_cs_data_set_camera_data(&program->cs_data, &program->camera);
        np_ssbo_set_data(program->cs_ssbo, &program->cs_data, 0, sizeof(mbs_cs_data));

        // calculate fractal
        np_dsa_texture_2d_bind_layout_unit(program->frame.texture, 0, GL_WRITE_ONLY, GL_RGBA32F); // stačí jen jednou?
        np_compute_program_use(program->compute_program, ceil(program->resolution_x / 8), ceil(program->resolution_y / 4), 1);

        // draw frame to screen
        //np_mesh_call_draw(&program->frame.mesh);
        
        np_mia_sys_mesh_draw_all(program->mesh_registry);
        //
        // GUI
        //
        
        time_diffrence += delta_time;
        if (time_diffrence > 25.0) { // update every 25ms
            // set camera stats text
            char camera_stats_buffer[256];
            sprintf_s(camera_stats_buffer, sizeof(camera_stats_buffer), "position xy: (%lf, %lf) zoom: %lf", program->camera.position_x, program->camera.position_y, program->camera.zoom);
            np_text_set(np_gui_text_get_text(program->ui.camera_stats), camera_stats_buffer);

            // set program stats text
            char program_stats_buffer[256];
            sprintf_s(program_stats_buffer, sizeof(program_stats_buffer), "ms: %lf fps: %u", delta_time, np_delta_time_to_fps(delta_time));
            np_text_set(np_gui_text_get_text(program->ui.program_stats), program_stats_buffer);
            
            char fractal_stats_buffer[256];
            sprintf_s(fractal_stats_buffer, sizeof(fractal_stats_buffer), "fractal type: Mandelbrot set; max iteration count: %i", program->cs_data.max_iteration_count);
            np_text_set(np_gui_text_get_text(program->ui.fractal_stats), fractal_stats_buffer);
            
            time_diffrence = 0.0;
        }
        
        // update (draw) GUI
        np_gui_update(&program->ui.gui_context, &program->window);

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

    }


    // close window
    if (event.type == NP_WINDOW_CLOSE_EVENT) {
        program->is_running = false;
        np_window_close(&program->window);
    }
}