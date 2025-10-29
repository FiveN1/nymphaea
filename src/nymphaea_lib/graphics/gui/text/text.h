#ifndef NP_GUI_TEXT_H
#define NP_GUI_TEXT_H

#include"nymphaea_lib/graphics/gui/context/gui_context.h"

#include"nymphaea_lib/graphics/text/text.h"
#include"nymphaea_lib/graphics/transform/transform_2d/transform_2d.h"

#include"nymphaea_lib/graphics/window/event/event.h"
//#include"os/window/window.h"

#include"nymphaea_lib/graphics/text/text_highlight/text_highlight.h"

#include"nymphaea_lib/graphics/window/input/input.h"


// ## GUI Text
// Text used in GUI applications.
typedef struct np_gui_text {
    np_text text;
    np_tr2 transform;

    // + highlight
    // + edit cursor
    // + flags
    
    //np_text_highlight highlight; // ZBAVIT SE !!

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


void np_gui_text_on_event(np_gui_text* gui_text, np_gui_context* gui_context, np_event event, np_window* window);



// tady použít np_shader?

#endif NP_GUI_TEXT_H