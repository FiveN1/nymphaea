#ifndef NP_GLYPH_H
#define NP_GLYPH_H

#include<glad/glad.h>

/*
* ## Glyph
* - stores data about a given glyph (character)
*/
typedef struct np_glyph {
    // glyph size
    GLfloat width;
    GLfloat height;
    // position offset
    GLfloat position_x;
    GLfloat position_y;
    // offset to next glyph
    GLfloat advance_offset;
    // texture position in atlas
    GLfloat uv_glyph_atlas_offset;
    // glyph texture size in atlas
    GLfloat uv_width;
    GLfloat uv_height;
} np_glyph;

#endif NP_GLYPH_H