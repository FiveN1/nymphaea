#ifndef NP_TEXT_HIGHLIGHT_H
#define NP_TEXT_HIGHLIGHT_H

#include"nymphaea_lib/graphics/mesh/mesh.h"
#include"nymphaea_lib/graphics/text/text.h"

#include"nymphaea_lib/graphics/transform/transform_2d/transform_2d.h"

#include"nymphaea_lib/graphics/window/event/event.h"

#include"nymphaea_lib/core/data_structures/array/array.h"

// NOT IMPLEMENTED

/*
* ## Text Highlight
*
* Mesh který vizualizuje vybrání textu.
* Vybraný text má počátek a také konec, takže jsou tu potřeba vědět 2 indexy.
* Text highlight funguje s np_text
*
*
*/
typedef struct np_text_highlight {
    np_mesh* mesh;
    np_tr2 transform;
    // mesh verticies
    np_array vertices;
    np_array indices;
} np_text_highlight;

void np_text_highlight_create(np_text_highlight* text_highlight, np_mesh* empty_mesh);

//void np_text_highlight_create(from, to); float begin_x, float begin_y, float end_x, float end_y


// highlight an area of text
void np_text_highlight_set(np_text_highlight* text_highlight, np_text* text, size_t begin, size_t end);


size_t np_text_highlight_get_index_by_position(np_text* text, float x, float y, float* char_x, float* char_y);


// v jiné tříde np_gui_text ? protože nemůže být tak abstraktní
//void np_text_highlight_on_event(np_text_highlight* text_highlight, np_text* text, np_event event);


#endif NP_TEXT_HIGHLIGHT_H