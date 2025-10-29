#include"pch.h"
#include"text_2d.h"

void np_text_2d_create(np_text_2d* text_2d, char* text_content, np_font* font, np_mesh* empty_mesh) {
    // create text
    np_text_create(&text_2d->text, text_content, font, empty_mesh);
    // create transform
    np_tr2_create(&text_2d->transform);
}

void np_text_2d_delete(np_text_2d* text_2d) {
    np_text_delete(&text_2d->text);
}

/*
void np_text_2d_set(np_text_2d* text_2d, char* text_content) {
    np_text_set(&text_2d->text, text_content);
}

void np_text_2d_set_position(np_text_2d* text_2d, vec2 position) {
    np_tr2_set_position(&text_2d->transform_2d, position);
}

void np_text_2d_set_orientation(np_text_2d* text_2d, vec2 orientation) {
    np_tr2_set_orientation(&text_2d->transform_2d, orientation);
}

void np_text_2d_set_scale(np_text_2d* text_2d, vec2 scale) {
    np_tr2_set_scale(&text_2d->transform_2d, scale);
}
*/

np_text* np_text_2d_get_text(np_text_2d* text_2d) {
    return &text_2d->text;
}

np_tr2* np_text_2d_get_transform(np_text_2d* text_2d) {
    return &text_2d->transform;
}