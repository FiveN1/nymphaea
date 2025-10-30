#ifndef NP_FONT_H
#define NP_FONT_H
// FreeType is included only into this file
#include<ft2build.h>
#include FT_FREETYPE_H

#include"glyph.h"
#include"nymphaea_lib/graphics/objects/texture_2d/texture_2d.h"
#include"nymphaea_lib/core/data_structures/array/array.h"

/*
* ## Font
* 
* a collection of glyph (character) data
*
* Using the FreeType library.
*
*/
typedef struct np_font {
    // texture holding all glyph textures
    np_texture_2d atlas;
    // size of the atlas
    GLsizei atlas_width;
    GLsizei atlas_height;
    // array of glyph data
    np_array glyphs;
    // font scale. used to scale all fonts to same size.
    GLfloat scale;
} np_font;

// load font instance.
// - np_font* font             -> font instance.
// - const char* font_filename -> file directory to load font from.
void np_font_create(np_font* font, const char* font_filename); // rename na np_font_load()?

// create font instance form alread loaded data.
void np_font_create_memory(np_font* font, const FT_Byte* font_file_data, FT_Long font_file_data_size);

// delete font instance.
// - np_font* font -> font instance.
void np_font_delete(np_font* font);

// get glyph atlas texture.
// - np_font* font -> font instance.
np_texture_2d np_font_get_atlas(np_font* font);

// get glyph atlas texture width.
// - np_font* font -> font instance.
GLsizei np_font_get_atlas_width(np_font* font);

// get glyph atlas texture height.
// - np_font* font -> font instance.
GLsizei np_font_get_atlas_height(np_font* font);

// get glyph (character) data.
// - np_font* font  -> font instance.
// - char character -> character to get info about.
np_glyph np_font_get_glyph(np_font* font, char character);

// get font y offset
// - np_font* font -> font instance.
GLfloat np_font_get_row_offset(np_font* font);

/* Zdroje:
*
* https://stackoverflow.com/questions/68855110/unable-to-upload-bitmaps-from-most-fonts-loaded-by-freetype-to-opengl-as-texture
* ft unicode : https://stackoverflow.com/questions/60526004/how-to-get-glyph-unicode-using-freetype
*
* __NULL_IMPORT_DESCRIPTOR warn: https://www.gamedev.net/forums/topic/645255-building-a-library-with-another-library/
*
* Link Error:
* external error: https://www.gamedev.net/forums/topic/700387-how-do-i-statically-link-freetype-in-vs2017/
* /MD https://stackoverflow.com/questions/14932262/multi-threaded-dll-md-vs-multi-threaded-mt
*
* LIBCMT confilict
* https://stackoverflow.com/questions/14148933/libcmt-conflicts-with-use-of-other-libs-unresolved-external-symbols
* - vše musí být v /MD
*
* Font sizes:
* https://joshcollinsworth.com/blog/never-use-px-for-font-size
*/

/* Změny
*
* [...]
*
* [09.10.2025] 
* přidána možnost načítání fontu z předem načtených souborů (byte dat)
*
* [10.10.2025] 
* začištění.
*
* [12.10.2025] 
* freetype překompilován aby nepotřeboval externí zdroje.
*
* [30.10.2025]
* všechny fonty teď mají stejnou počátešní velikost.
* default velikost není nějak přesně určená, tak by yblo dobré nějak vypočítat, třeba 12 font je 16px.
*
*/

#endif NP_FONT_H