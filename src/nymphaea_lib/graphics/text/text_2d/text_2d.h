#ifndef NP_TEXT_2D_H
#define NP_TEXT_2D_H

#include"nymphaea_lib/graphics/text/text.h"
#include"nymphaea_lib/graphics/transform/transform_2d/transform_2d.h"

// ODSTRANIT SHADER !!
// SHADER BUDE V GUI TEXT !!

/*
* ## Text 2D
* Text rendered in 2-Dimensions
*/
typedef struct np_text_2d {
    np_text text;
    np_transform_2d transform;
} np_text_2d;

// create 2D text.
void np_text_2d_create(np_text_2d* text_2d, char* text_content, np_font* font, np_mesh* empty_mesh);
// clear 2D text data.
void np_text_2d_delete(np_text_2d* text_2d);

np_text* np_text_2d_get_text(np_text_2d* text_2d);

np_transform_2d* np_text_2d_get_transform(np_text_2d* text_2d);



// set 2d text content
//void np_text_2d_set(np_text_2d* text_2d, char* text_content);
// set 2d text position
//void np_text_2d_set_position(np_text_2d* text_2d, vec2 position);
// set 2d text orientation
//void np_text_2d_set_orientation(np_text_2d* text_2d, vec2 orientation);
// set 2d text scale
//void np_text_2d_set_scale(np_text_2d* text_2d, vec2 scale);

#endif NP_TEXT_2D_H