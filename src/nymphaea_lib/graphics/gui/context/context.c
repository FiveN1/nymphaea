#include"pch.h"
#include"context.h"
// elements supported by gui
#include"nymphaea_lib/graphics/gui/text/text.h"

void np_gui_create(np_gui_context* gui_context) {
    // the maximum amount of registries is set by the number of enums in 'np_gui_elements'
    // NOTE: the order of element registres does not matter in mia!
    //
    // the 'registry_types' array keeps track of the type of registries allocated.
    // in this array the index corresponds to an element. so the first index at '0' woud be the first enum in 'np_gui_elements' (NP_GUI_TEXT)
    // the value at this idex is the index of registry in mia.
    //
    // if a value in 'registry_types' is equal to '_NP_GUI_END_ENUM' it means its not valid.
    // since there are '_NP_GUI_END_ENUM' amount of registries this value woud be out of range.
    
    // the amount af possible registries in proportional to amount of possible types.
    const size_t registry_count = _NP_GUI_END_ENUM - _NP_GUI_BEGIN_ENUM - 1;
    // create elements
    np_mia_create(&gui_context->elements, registry_count);
    // create array of type indexes.
    // this array will hold an index of registry of type. the type is based on id of given value.
    np_array_create(&gui_context->registry_types, registry_count, sizeof(size_t));
    // set array values to 'element not enabled'
    for (size_t i = 0; i < np_array_get_size(&gui_context->registry_types); i++) {
        ((size_t*)np_array_data(&gui_context->registry_types))[i] = _NP_GUI_BEGIN_ENUM;
    }

    //
    // other
    //

    // create mesh registry
    np_id_array_create(&gui_context->mesh_registry, 512, sizeof(np_mesh));
    // load font
    // "C:\\Programing\\_C\\Nymphaea\\assets\\font\\ProggyClean\\ProggyClean.ttf"
    np_font_create(&gui_context->default_font, "C:\\Programing\\_C\\Nymphaea\\assets\\font\\arial\\arial.ttf");

    gui_context->default_text_shader = np_shader_program_load("C:\\Programing\\_C\\Nymphaea\\nymphaea\\src\\graphics\\gui\\context\\shader\\text.vert", "", "C:\\Programing\\_C\\Nymphaea\\nymphaea\\src\\graphics\\gui\\context\\shader\\text.frag");
    gui_context->default_color_shader = np_shader_program_load("C:\\Programing\\_C\\Nymphaea\\nymphaea\\src\\graphics\\gui\\context\\shader\\color.vert", "", "C:\\Programing\\_C\\Nymphaea\\nymphaea\\src\\graphics\\gui\\context\\shader\\color.frag");

    np_camera_2d_create(&gui_context->camera);


    glm_vec4_copy((vec4){0.9f, 0.7f, 0.0f, 1.0f}, gui_context->text_highlight_color);
}

void np_gui_delete(np_gui_context* gui_context) {
    //...
}

// get size of data type based on enum.
size_t np_gui_get_element_size(np_gui_elements element) {
    switch (element) {
        case NP_GUI_TEXT:
            return sizeof(np_gui_text);
            break;
        case NP_GUI_INT:
            return sizeof(int);
            break;
    }
    // invalid
    return 0;
}

void np_gui_enable(np_gui_context* gui_context, np_gui_elements element, size_t amount) {
    // size of type stored in registry.
    size_t element_size = np_gui_get_element_size(element);
    np_assert(element_size != 0, "np_gui: invalid element");
    // create registry based on avalible types.
    size_t id = np_id_array_get_id_by_ptr(&gui_context->elements, np_mia_registry_create(&gui_context->elements, amount, element_size));
    // link registry with element.
    ((np_gui_elements*)np_array_data(&gui_context->registry_types))[element - _NP_GUI_BEGIN_ENUM - 1] = id;
}

// get registry if of element.
// if element is not enabled or does not exist, returns '_NP_GUI_END_ENUM'.
size_t np_gui_get_element_registry_id(np_gui_context* gui_context, np_gui_elements element) {
    // get element from array
    size_t* p_id = (size_t*)np_array_get(&gui_context->registry_types, element - _NP_GUI_BEGIN_ENUM - 1);
    // check if element exists
    if (p_id == NULL) return _NP_GUI_END_ENUM; // možná vrátit: _NP_GUI_END_ENUM - _NP_GUI_BEGIN_ENUM - 1 ??
    // return stored value
    return *p_id;
}

np_mia_registry* np_gui_get_elements(np_gui_context* gui_context, np_gui_elements element) {
    // get pointer to element id.
    size_t id = np_gui_get_element_registry_id(gui_context, element);
    // check if valid
    np_assert(id != _NP_GUI_END_ENUM, "np_gui: element not enabled");
    // return pointer to element registry.
    return (np_mia_registry*)np_id_array_get(&gui_context->elements, id);
}

void np_gui_update(np_gui_context* gui_context, np_window* window) {
    // update camera
    np_camera_2d_update(&gui_context->camera, np_window_get_width(window), np_window_get_height(window));
    // draw
    glDisable(GL_DEPTH_TEST);

    //np_mia_sys_mesh_draw_all(&gui_context->mesh_registry);
    for (size_t i = 0; i < np_mia_registry_get_size(&gui_context->mesh_registry); i++) {
        np_mesh* mesh = (np_mesh*)np_mia_get_by_id(&gui_context->mesh_registry, i);
        np_mesh_call_draw(mesh);
    }

    glEnable(GL_DEPTH_TEST);
}

void np_gui_on_event(np_gui_context* gui_context, np_event event, np_window* window) {

    // update texts
    //size_t id = np_gui_get_element_registry_id(element);
    //if (id != _NP_GUI_END_ENUM) {

    //}

    // check zda enabled!!!
    np_mia_registry* texts = np_gui_get_elements(gui_context, NP_GUI_TEXT);
    for (size_t i = 0; i < np_mia_registry_get_size(texts); i++) {
        np_gui_text_on_event((np_gui_text*)np_mia_get_by_id(texts, i), gui_context, event, window);
    }

}