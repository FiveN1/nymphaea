#ifndef NP_GUI_CONTEXT_H
#define NP_GUI_CONTEXT_H

#include"nymphaea_lib/core/mia/mia.h"
#include"nymphaea_lib/core/data_structures/array/array.h"
//
#include"nymphaea_lib/graphics/font/font.h"
#include"nymphaea_lib/graphics/objects/shader_program/shader_program.h"
#include"nymphaea_lib/graphics/camera/camera_2d/camera_2d.h"
#include"nymphaea_lib/graphics/window/window.h"

// shaders
#include"shader/shader.h"

// ## GUI Context
// holds all nymphaea GUI data.
typedef struct np_gui_context { // rename na np_gui?
    // core
    np_mia elements;
    np_array registry_types;
    //
    np_id_array mesh_registry;
    np_font default_font;
    np_shader_program default_text_shader; // vyměnit za np_shader?
    np_shader_program default_color_shader;
    np_camera_2d camera;

    vec4 text_highlight_color;

    //np_shader default_text_shader;

    // co bude gui obsahovat?
    // + camera_2d
    // + default font
    // + shadery
    // + box mesh data
    // + text shader

} np_gui_context;

typedef enum np_gui_elements {
    _NP_GUI_BEGIN_ENUM = 0,
    // types supported by np_gui
    NP_GUI_TEXT,
    NP_GUI_INT,
    // ...
    // end enum used for ivnalid value or for getting the size of this enum array.
    _NP_GUI_END_ENUM
} np_gui_elements;

// create nymphaea gui context.
// - np_gui_context* gui_context -> gui context instance.
void np_gui_create(np_gui_context* gui_context);
// delete nymphaea gui context.
// - np_gui_context* gui_context -> gui context instance.
void np_gui_delete(np_gui_context* gui_context);
// enable an element in gui with maximum amount of elements gui can have.
// - np_gui_context* gui_context -> gui context instance.
// - np_gui_elements element     -> enabled element.
// - size_t amount               -> amount of elements gui can store.
void np_gui_enable(np_gui_context* gui_context, np_gui_elements element, size_t amount);
// get element registry of enabled element.
// - np_gui_context* gui_context -> gui context instance.
// - np_gui_elements element     -> enabled element.
np_mia_registry* np_gui_get_elements(np_gui_context* gui_context, np_gui_elements element);
// update nymphaea gui context.
// - np_gui_context* gui_context -> gui context instance.
void np_gui_update(np_gui_context* gui_context, np_window* window);

void np_gui_on_event(np_gui_context* gui_context, np_event event, np_window* window);


// možná mít všechny elementy zapnuté?
// ale potom si nemůžeš určovat počet elementů... a musel bys vymyslet nějakej id systém pro všechny shadery a elementy...

/* Změny:
*
* [...]
* [08.10.2025] přidán embeded shader source code. (ještě přidata embeded font!) 
* nelepší bude vytvořit nějaký struct? nebo kde bych to mohl uložit?
* [09.10.2025] přidán embeded font. embeded zdroje jsou v gui_resources ve formě funkcí.
* ty data jsou v funkcícch, kde jsou allokována a potom uvolněna (ve funkci) takže nezaplnuje zbytečně pamět.
*
*
*/

#endif NP_GUI_CONTEXT_H