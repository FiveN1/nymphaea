#include"pch.h"
#include"font.h"

/*
* TODO:
* - add spacing between glyphs in the atlas texture
*
* - udělat čistější.
*/

//
// private define
//

void np_font_create_from_face(np_font* font, FT_Face face);

//
// implementation
//

void np_font_create(np_font* font, const char* font_filename) {
    // load the free-type library
    FT_Library ft;
    np_assert(!FT_Init_FreeType(&ft), "np_font: could not init FreeType library");
    // load font 
    FT_Face face;
    np_assert(!FT_New_Face(ft, font_filename, 0, &face), "np_font: failed to load font");
    // set font from face
    np_font_create_from_face(font, face);
    // clear
    FT_Done_Face(face);
    FT_Done_FreeType(ft);
}

void np_font_create_memory(np_font* font, const FT_Byte* font_file_data, FT_Long font_file_data_size) {
    // load the free-type library
    FT_Library ft;
    np_assert(!FT_Init_FreeType(&ft), "np_font: could not init FreeType library");
    // load font face
    FT_Face face;
    np_assert(!FT_New_Memory_Face(ft, font_file_data, font_file_data_size, 0, &face), "np_font: failed to load font");
    // set font from face
    np_font_create_from_face(font, face);
    // clear
    FT_Done_Face(face);
    FT_Done_FreeType(ft);
}

void np_font_delete(np_font* font) {
    np_array_delete(&font->glyphs);
    np_texture_2d_delete(&font->atlas);
}

np_texture_2d np_font_get_atlas(np_font* font) {
    return font->atlas;
}

GLsizei np_font_get_atlas_width(np_font* font) {
    return font->atlas_width;
}

GLsizei np_font_get_atlas_height(np_font* font) {
    return font->atlas_height;
}

np_glyph np_font_get_glyph(np_font* font, char character) {
    np_glyph* glyph = (np_glyph*)np_array_get(&font->glyphs, character);
    // if glyph not valid return first glyph
    if (glyph == NULL) glyph = (np_glyph*)np_array_get(&font->glyphs, 0);
    return *glyph;
}

GLfloat np_font_get_row_offset(np_font* font) {
    return (GLfloat)font->atlas_height * font->scale;
}

//
// private implementation
//

void np_font_create_from_face(np_font* font, FT_Face face) {
    // font resolution
    FT_Set_Pixel_Sizes(face, 0, 48);
    // Disable byte-alignment restriction
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    // empty glyph atlas initialization

    // init sizes
    font->atlas_width = 0;
    font->atlas_height = 0;
    // get width & height of atlas
    for (GLubyte c = 0; c < 128; c++) {
        if (FT_Load_Char(face, c, FT_LOAD_RENDER)) {
            np_log_error("np_font: failed to load glyph");
            continue;
        }
        font->atlas_width += face->glyph->bitmap.width;
        if ((unsigned int)font->atlas_height < face->glyph->bitmap.rows) { 
            font->atlas_height = face->glyph->bitmap.rows;
        };
    }
    // create the glyph atlas texture
    np_texture_2d_create_empty(&font->atlas, font->atlas_width, font->atlas_height, GL_RED, GL_NEAREST, GL_CLAMP_TO_EDGE);
    
    // glyph data retrival

    // TODO: scale all fonts to one UNIVERSAL value
    // aby všechny texty měli stejnou velikost
    font->scale = 0.001f;

    // create array of glyph data
    np_array_create(&font->glyphs, 128, sizeof(np_glyph));
    //np_dynamic_array_create(&font->glyphs, 128, sizeof(np_glyph));
    // current glyph texture offset in the atlas texture
    GLint glyph_atlas_offset = 0;;
    // loop for all of characters
    for (GLubyte c = 0; c < 128; c++) {
        // load character glyph
        if (FT_Load_Char(face, c, FT_LOAD_RENDER)) {
            np_log_error("np_font: failed to load glyph");
            continue;
        }
        // draw glyph to the atlas
        np_texture_2d_set_pixels(font->atlas, glyph_atlas_offset, 0, face->glyph->bitmap.width, face->glyph->bitmap.rows, GL_RED, face->glyph->bitmap.buffer);
        // store glyph data
        np_glyph glyph;
        // glyph size on screen. the size is scaled to universal value
        glyph.width = (GLfloat)face->glyph->bitmap.width * font->scale;
        glyph.height = (GLfloat)face->glyph->bitmap.rows * font->scale;
        // glyph position relative to its offset. the size is scaled to universal value
        glyph.position_x = (GLfloat)face->glyph->bitmap_left * font->scale;
        glyph.position_y = (GLfloat)face->glyph->bitmap_top * font->scale;
        // advance cursors for next glyph (note that advance is number of 1 / 64 pixels). bitshift by 6 to get value in pixels(2 ^ 6 = 64)
        glyph.advance_offset = (GLfloat)(face->glyph->advance.x >> 6) * font->scale;
        // horizontal offset in font atlas of current glyph.
        glyph.uv_glyph_atlas_offset = (GLfloat)glyph_atlas_offset;
        // uv size of glyph in atlas.
        glyph.uv_width = (GLfloat)face->glyph->bitmap.width;
        glyph.uv_height = (GLfloat)face->glyph->bitmap.rows;
        // add glyph to array
        ((np_glyph*)np_array_data(&font->glyphs))[c] = glyph;
        // set the next glyph atlas offset
        glyph_atlas_offset += face->glyph->bitmap.width;
    }
}


// Zdroje:
// https://stackoverflow.com/questions/68855110/unable-to-upload-bitmaps-from-most-fonts-loaded-by-freetype-to-opengl-as-texture
// ft unicode : https://stackoverflow.com/questions/60526004/how-to-get-glyph-unicode-using-freetype
//
// __NULL_IMPORT_DESCRIPTOR warn: https://www.gamedev.net/forums/topic/645255-building-a-library-with-another-library/
//
// Link Error:
// external error: https://www.gamedev.net/forums/topic/700387-how-do-i-statically-link-freetype-in-vs2017/
// /MD https://stackoverflow.com/questions/14932262/multi-threaded-dll-md-vs-multi-threaded-mt
//
// LIBCMT confilict
// https://stackoverflow.com/questions/14148933/libcmt-conflicts-with-use-of-other-libs-unresolved-external-symbols
// - vše musí být v /MD