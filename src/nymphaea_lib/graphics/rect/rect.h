#ifndef NP_RECT_H
#define NP_RECT_H

#include"nymphaea_lib/graphics/transform/transform_2d/transform_2d.h"

//#define NP_DEBUG_SHOW_RECT_OUTLINE

/*
* ## Rect
*
* A rectangle struct holding data about a rectangle.
* its very usefull as a hitbox.
*
* NOTE: Rect origin is in the top left corner
*
*/
typedef struct np_rect {
    np_transform_2d transform_2d;
    vec2 size;
} np_rect;

// create rect instance
void np_rect_create(np_rect* rect);
// get rect transform
np_transform_2d* np_rect_get_transform_2d(np_rect* rect);
// set rect size
void np_rect_set_size(np_rect* rect, vec2 size);
// check if a given point is or is not in a rect
bool np_rect_check_point(np_rect* rect, vec2 point);

// vizulize with lines?
// with some sort of debug context...

// použivat funkce !! np_rect_get_transform_2d třeba

#endif NP_RECT_H