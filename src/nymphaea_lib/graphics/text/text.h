#ifndef NP_TEXT_H
#define NP_TEXT_H

#include"nymphaea_lib/graphics/mesh/mesh.h"
#include"nymphaea_lib/graphics/font/font.h"
#include"nymphaea_lib/core/data_structures/array/array.h"

#include"text_mesh/text_mesh.h"

// text.h by FiveN

/*
* ## Text
* - display text on the screen!
* - fast text update.
* - flexible. can be used in 2D or 3D.
* - creates a mesh, with texture from font to render text.
*/
typedef struct np_text {
    // the text
    char* string;
    size_t string_length;
    // font ptr
    np_font* font;
    //
    np_text_mesh text_mesh;

    // přidat text highlight
    // outline?
    // https://gamedev.stackexchange.com/questions/46490/font-outline-in-opengl-ftgl

} np_text;

// create text instance.
// #### Parameters
// - np_text* text       -> text instance.
// - char* text_string   -> string of text to be displayed by text instance.
// - np_font* font       -> pointer to a font instance.
// - np_mesh* empty_mesh -> pointer to free memory, that will be used to store text mesh. done this way to store all emshes in one array, so it is easy and fast to draw.
void np_text_create(np_text* text, char* string, np_font* font, np_mesh* empty_mesh);
// delete text instance.
// #### Parameters
// - np_text* text -> text instance.
void np_text_delete(np_text* text);
// change the text.
// Can be slow if new text is larger then before, because it needs to allocate new larger buffer for the data.
// #### Parameters
// - np_text* text      -> text instance.
// - char* text_content -> string of text to be displayed by text instance.
void np_text_set(np_text* text, char* string);
// get mesh of text.
// #### Parameters
// - np_text* text -> text instance.
np_mesh* np_text_get_mesh(np_text* text);
// set text font.
// #### Parameters
// - np_text* text -> text instance.
// - np_font* font -> pointer to a font instance.
void np_text_set_font(np_text* text, np_font* font);

char* np_text_get_string(np_text* text);


// TODO:
// přidat funkce které upraví jenom usek textu
// přidat také funkci která upraví usek textu na jiný font? nebo iný mesh??
//
// přidat higlight sem!!!

/*
* Změny:
*
* [...] 
* hodně změn
*
* [31.05.2025] 
* uprava komentářů
*
* [13.06.2025] 
* při tvorbě textu je content textu allocován kdyby originální kontent byl deallocován. bezpečné.
* začištění kodu
*
* [29.10.2025]
* logika pro generování meshe přesunuta do text_mesh.c
*
* [30.10.2025]
* začištěno.
*
*/

#endif NP_TEXT_H