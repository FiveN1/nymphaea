#include"pch.h"
#include"text.h"

np_gui_text* np_gui_text_create(np_gui_context* gui_context, char* text_string) {
    // allocate space for text
    np_gui_text* gui_text = np_mia_alloc(np_gui_get_elements(gui_context, NP_GUI_TEXT));
    
    // create text
    np_text_create(&gui_text->text, text_string, &gui_context->default_font, np_mia_alloc(&gui_context->mesh_registry));
    
    // create transform
    np_tr2_create(&gui_text->transform);

    // set text shader
    np_shader_data* shader_data = np_mesh_set_shader(np_text_get_mesh(&gui_text->text), &gui_context->default_text_shader);
    *(np_texture_2d*)np_shader_data_get(shader_data, "glyph") = np_font_get_atlas(&gui_context->default_font);
    *(mat3**)np_shader_data_get(shader_data, "model_matrix") = np_tr2_get(&gui_text->transform);
    *(mat3**)np_shader_data_get(shader_data, "view_matrix") = np_tr2_get(&gui_context->camera.transform);
    *(mat4**)np_shader_data_get(shader_data, "proj_matrix") = np_camera_2d_get_matrix(&gui_context->camera);

    // return allocated address
    return gui_text;
}

void np_gui_text_delete(np_gui_text* gui_text) {
    np_text_delete(&gui_text->text);
}

np_text* np_gui_text_get_text(np_gui_text* gui_text) {
    return &gui_text->text;
}

np_tr2* np_gui_text_get_transform(np_gui_text* gui_text) {
    return &gui_text->transform;
}

void np_gui_text_set_font(np_gui_text* gui_text, np_font* font) {
    np_text_set_font(&gui_text->text, font);
    np_shader_data* shader_data = (np_shader_data*)np_mesh_get_draw_data(np_text_get_mesh(&gui_text->text));
    *(np_texture_2d*)np_shader_data_get(shader_data, "glyph") = np_font_get_atlas(font);
}