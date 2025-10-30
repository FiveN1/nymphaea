#ifndef NP_GUI_TEXT_H
#define NP_GUI_TEXT_H

#include"nymphaea_lib/graphics/gui/context/gui_context.h"

#include"nymphaea_lib/graphics/text/text.h"
#include"nymphaea_lib/graphics/transform/transform_2d/transform_2d.h"

/*
* ## GUI Text
*
* Text used in GUI applications.
*
*/
typedef struct np_gui_text {
    np_text text;
    np_tr2 transform;
} np_gui_text;

// create gui text in gui context.
// - np_gui_context* gui_context -> gui context instance.
// - char* text_string           -> string you want to show on screen.
np_gui_text* np_gui_text_create(np_gui_context* gui_context, char* text_string);

// delete gui text instance.
// - np_gui_text* gui_text -> gui text instance.
void np_gui_text_delete(np_gui_text* gui_text);

// get text of gui text.
// - np_gui_text* gui_text -> gui text instance.
np_text* np_gui_text_get_text(np_gui_text* gui_text);

// get transform of gui text.
// - np_gui_text* gui_text -> gui text instance.
np_tr2* np_gui_text_get_transform(np_gui_text* gui_text);

void np_gui_text_set_font(np_gui_text* gui_text, np_font* font);


// tady použít np_shader?

/*
* Změny
*
* [...]
*
* [30.10.2025]
* začištěn text, odstraněn nefunkční highlight, všě je čitelné.
* přidána 'np_gui_text_set_font()' funkce.
*
*/

#endif NP_GUI_TEXT_H