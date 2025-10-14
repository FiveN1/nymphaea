#include"pch.h"
#include"text.h"

np_gui_text* np_gui_text_create(np_gui_context* gui_context, char* text_string) {
    // allocate space for text
    np_gui_text* gui_text = np_mia_alloc(np_gui_get_elements(gui_context, NP_GUI_TEXT));
    // create highlight
    // NOTE: this first so that the mesh is rendered behind the text
    np_text_highlight_create(&gui_text->highlight, np_mia_alloc(&gui_context->mesh_registry));
    // set highlight shader
    np_mesh_set_shader_program(gui_text->highlight.mesh, gui_context->default_color_shader);
    np_mesh_set_draw_callback(gui_text->highlight.mesh, &np_gui_color_shader_use);
    np_gui_color_shader_data* data2 = (np_gui_color_shader_data*)np_mesh_set_draw_data(gui_text->highlight.mesh, sizeof(np_gui_color_shader_data));
    data2->text_transform = &gui_text->transform;
    data2->camera_2d = &gui_context->camera;
    glm_vec4_copy(gui_context->text_highlight_color, data2->color);
    // create text
    np_text_create(&gui_text->text, text_string, &gui_context->default_font, np_mia_alloc(&gui_context->mesh_registry));
    // set text shader
    np_mesh_set_shader_program(np_text_get_mesh(&gui_text->text), gui_context->default_text_shader);
    np_mesh_set_draw_callback(np_text_get_mesh(&gui_text->text), &np_gui_text_shader_use);
    np_gui_text_shader_data* data = (np_gui_text_shader_data*)np_mesh_set_draw_data(np_text_get_mesh(&gui_text->text), sizeof(np_gui_text_shader_data));
    data->font_atlas = np_font_get_atlas(&gui_context->default_font);
    data->text_transform = &gui_text->transform;
    data->camera_2d = &gui_context->camera;
    // create transform
    np_transform_2d_create(&gui_text->transform);
    // return allocated address
    return gui_text;
}

void np_gui_text_delete(np_gui_text* gui_text) {
    np_text_delete(&gui_text->text);
}

np_text* np_gui_text_get_text(np_gui_text* gui_text) {
    return &gui_text->text;
}

np_transform_2d* np_gui_text_get_transform(np_gui_text* gui_text) {
    return &gui_text->transform;
}

void np_gui_text_project_point(np_camera_2d* camera, np_transform_2d* transform, float in_x, float in_y, float* out_x, float* out_y) {
    // reverse projection
    vec4 p1 = {in_x, in_y, 1.0f, 1.0f};
    // verse projection matrix
    mat4 m4;
    glm_mat4_inv(*np_camera_2d_get_matrix(camera), m4);
    glm_mat4_mulv(m4, p1, p1);
    //
    vec3 point_projected = {p1[0], p1[1], 1.0};
    // reverse view matrix
    mat3 m3;
    glm_mat3_inv(*np_transform_2d_get(np_camera_2d_get_transform(camera)), m3);
    glm_mat3_mulv(m3, point_projected, point_projected);
    // revers model matrix
    glm_mat3_inv(*np_transform_2d_get(transform), m3);
    glm_mat3_mulv(m3, point_projected, point_projected);
    // return
    *out_x = point_projected[0];
    *out_y = point_projected[1];
}

void np_gui_text_on_event(np_gui_text* gui_text, np_gui_context* gui_context, np_event event, np_window* window) {
    // update highlight...
    return;
    static bool highlighting = false;
    static size_t begin_id = 0;

    // ckeck pro stisk nebo puštění tlačítka myši.
    if (event.type == NP_MOUSE_BUTTON_EVENT)  {
        if (event.mouse_button_event.button == GLFW_MOUSE_BUTTON_LEFT) {
            if (event.mouse_button_event.action == GLFW_PRESS) {
                // window point
                double mouse_x, mouse_y;
                np_get_mouse_position_stretch(window, &mouse_x, &mouse_y);
                // projected point
                float point_x, point_y;
                np_gui_text_project_point(&gui_context->camera, np_gui_text_get_transform(gui_text), (float)mouse_x, (float)mouse_y, &point_x, &point_y);
                
                // TODO: clamp to edge
                
                if (point_x < 0.0f) point_x = 0.0f;
                if (point_y > 0.0f) point_y = 0.0f;
                // clamp VĚTŠÍCH VELIKOSTÍ JE V FUNKCI np_text_get_index_by_position (PŘEDĚLAT NA SPECIÁLNÍ FUNKCI S CLAMP??)

                //if (point_x > 1.0f)

                np_print("point: %f, %f", point_x, point_y);
                
                // get intersected letter id
                size_t id = np_text_get_index_by_position_clamp(np_gui_text_get_text(gui_text), point_x, point_y);
                // nastaví se status highlightu
                highlighting = true;
                begin_id = id;
                // pokud je mimo text tak se vybere první index
                // TODO: dodělat aby se vybral index podle toho z jaké strany se vybírá. (inspirovat se z html)
                if (id == (size_t)-1) {
                    begin_id = 0;
                    // clear mesh
                    np_text_highlight_set(&gui_text->highlight, np_gui_text_get_text(gui_text), 0, 0);


                    // clamp to border.

                }
            } else {
                highlighting = false;
            }
        }
    }


    // TODO: pokud start byl někde mimo text tak aby highlight začal s indexem 0 !!

    // pokud je myš držena ale vznikl nějaký nový update. třeba že se myš posunula.
    if (event.type == NP_MOUSE_MOVE_EVENT) { 
        if (highlighting) {
            // window point
            double mouse_x, mouse_y;
            np_get_mouse_position_stretch(window, &mouse_x, &mouse_y);
            // projected point
            float point_x, point_y;
            np_gui_text_project_point(&gui_context->camera, np_gui_text_get_transform(gui_text), (float)mouse_x, (float)mouse_y, &point_x, &point_y);
            // get intersected letter id
            size_t id = np_text_get_index_by_position_clamp(np_gui_text_get_text(gui_text), point_x, point_y);

            if (id != (size_t)-1) {
                np_text_highlight_set(&gui_text->highlight, np_gui_text_get_text(gui_text), begin_id, id);
            } else {
                np_text_highlight_set(&gui_text->highlight, np_gui_text_get_text(gui_text), 0, 0);
            }
        }
    }



    /*
    
    

            Text
        
    
    */



}