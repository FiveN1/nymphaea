#include"pch.h"
#include"text.h"
#include"nymphaea_lib/core/data_structures/array/array.h"

void np_text_create(np_text* text, char* string, np_font* font, np_mesh* empty_mesh) {
    // string content
    text->string_length = 0;
    text->string = NULL;
    // font reference
    text->font = font;
    // create text mesh
    np_text_mesh_create(&text->text_mesh, empty_mesh);
    // set text mesh
    np_text_set(text, string);
}

void np_text_delete(np_text* text) {
    text->string_length = 0;
    free(text->string);
    // delete text mesh
    np_text_mesh_delete(&text->text_mesh);
}

void np_text_set(np_text* text, char* string) {
    // copy string
    size_t string_length = strlen(string);
    size_t string_buffer_size = sizeof(char) * (string_length + 1);

    // velikost text bufferu může být jenom větší
    // z bezpečnostních důvodu je string kopírován jelikož originální zdroj může být deallocován.
    if (string_length > text->string_length) {
        text->string_length = string_length;
        text->string = realloc(text->string, string_buffer_size);
    }

    // nakonec zkopírujem string do bufferu
    strcpy_s(text->string, string_buffer_size, string);

    // create mesh
    np_text_mesh_generate(&text->text_mesh, text->font, string, string_length);
}

np_mesh* np_text_get_mesh(np_text* text) {
    return text->text_mesh.mesh;
}

void np_text_set_font(np_text* text, np_font* font) {
    text->font = font;
}

char* np_text_get_string(np_text* text) {
    return text->string;
}
