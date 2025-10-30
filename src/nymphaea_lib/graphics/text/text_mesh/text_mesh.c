#include"pch.h"
#include"text_mesh.h"

//
// local definice
//

// nastavíme novou velikost pro meshdata podle délky textu
void np_text_mesh_resize_mesh_data(np_mesh_data* mesh_data, size_t text_len);
// create rect for character in mesh data.
void np_text_mesh_data_set_char_rect(np_mesh_data mesh_data, np_glyph glyph, np_font* font, GLfloat offset_x, GLfloat offset_y, size_t indices_offset);

//
// implementace
//

void np_text_mesh_create(np_text_mesh* text_mesh, np_mesh* empty_mesh) {
    // mesh create
    text_mesh->mesh = empty_mesh;
    // nastavíme text mesh attributy. (XY, UV)
    // pole se nemaže jelikož tu zůstane po celou dobu textu.
    GLuint attributes_size = 2 * sizeof(GLuint);
    GLuint* attributes = malloc(attributes_size);
    attributes[0] = 2;
    attributes[1] = 2;
    text_mesh->mesh_data = (np_mesh_data){NULL, 0, NULL, 0, attributes, attributes_size};
    // create mesh. mesh data will be set in the create_text_mesh() function
    np_mesh_create(text_mesh->mesh, text_mesh->mesh_data);

}

void np_text_mesh_delete(np_text_mesh* text_mesh) {
    text_mesh->mesh = NULL; // free meshe je mimo tuto funkci.
    np_mesh_data_free(text_mesh->mesh_data);
}

// PROBLÉM:
// při strlen se počítají i newline, které není potřeba allocovat!
void np_text_mesh_generate(np_text_mesh* text_mesh, np_font* font, char* string, size_t string_len) {
    // resize if larger
    size_t prev_text_len = text_mesh->mesh_data.vertices_size / sizeof(GLfloat) / (4 * 4); // je vylepšit ?
    if (string_len > prev_text_len) np_text_mesh_resize_mesh_data(&text_mesh->mesh_data, string_len);

    // current text offset (like in a typewriter)
    GLfloat offset_x = 0.0f;
    GLfloat offset_y = 0.0f;

    // create a rect for every character in text
    for (size_t char_index = 0; char_index < string_len; char_index++)  {
        // change y offset if newline character encountered
        if (string[char_index] == '\n') {
            offset_x = 0.0f;
            offset_y -= np_font_get_row_offset(font);
            continue;
        }
        // get glyph data
        np_glyph glyph = np_font_get_glyph(font, string[char_index]);
        // vytvoříme rect pro char
        np_text_mesh_data_set_char_rect(text_mesh->mesh_data, glyph, font, offset_x, offset_y, char_index);
        // move on to next char position
        offset_x += glyph.advance_offset;
    }

    // set new mesh data
    np_mesh_set_mesh_data(text_mesh->mesh, text_mesh->mesh_data, GL_DYNAMIC_DRAW, GL_DYNAMIC_DRAW);
}

//
// local implementace
//

void np_text_mesh_resize_mesh_data(np_mesh_data* mesh_data, size_t text_len) {
    // každý char ma 4 vertexy, každý vertex 4 float. (X, Y, U, V)
    mesh_data->vertices_size = text_len * 4 * 4 * sizeof(GLfloat);
    // každý char má 6 indexů. (2 trojuhelníky = 2 * 3 indexy)
    mesh_data->indices_size = text_len * 6 * sizeof(GLuint);

    // realloc vertices
    mesh_data->vertices = realloc(mesh_data->vertices, mesh_data->vertices_size);
    np_assert(mesh_data->vertices != NULL || mesh_data->vertices_size == 0, " np_text_mesh: realloc error!");
    // realloc indices
    mesh_data->indices = realloc(mesh_data->indices, mesh_data->indices_size);
    np_assert(mesh_data->indices != NULL || mesh_data->vertices_size == 0, " np_text_mesh: realloc error!");
}

void np_text_mesh_data_set_char_rect(np_mesh_data mesh_data, np_glyph glyph, np_font* font, GLfloat offset_x, GLfloat offset_y, size_t char_index) {
    // glyph position
    GLfloat glyph_max_height = np_font_get_row_offset(font);
    GLfloat glyph_width = glyph.width;
    GLfloat glyph_height = glyph.height;
    GLfloat glyph_pos_x = offset_x + glyph.position_x;
    GLfloat glyph_pos_y = offset_y - (glyph_height - glyph.position_y);
    // glyph UV coordinates in the font atlas
    GLfloat glyph_uv_x_base = glyph.uv_glyph_atlas_offset / font->atlas_width;
    GLfloat glyph_uv_x_max = (glyph.uv_glyph_atlas_offset + glyph.uv_width) / font->atlas_width;
    GLfloat glyph_uv_y_base = 0.0f;
    GLfloat glyph_uv_y_max = glyph.uv_height / font->atlas_height;
    // set vertex data of the current character box
    size_t char_vert_begin = char_index * 16;
    // top-left
    mesh_data.vertices[char_vert_begin + 0] = glyph_pos_x;
    mesh_data.vertices[char_vert_begin + 1] = glyph_pos_y + glyph_height - glyph_max_height;
    mesh_data.vertices[char_vert_begin + 2] = glyph_uv_x_base;
    mesh_data.vertices[char_vert_begin + 3] = glyph_uv_y_base;
    // bottom-left
    mesh_data.vertices[char_vert_begin + 4] = glyph_pos_x;
    mesh_data.vertices[char_vert_begin + 5] = glyph_pos_y - glyph_max_height;
    mesh_data.vertices[char_vert_begin + 6] = glyph_uv_x_base;
    mesh_data.vertices[char_vert_begin + 7] = glyph_uv_y_max;
    // bottom-right
    mesh_data.vertices[char_vert_begin + 8] = glyph_pos_x + glyph_width;
    mesh_data.vertices[char_vert_begin + 9] = glyph_pos_y - glyph_max_height;
    mesh_data.vertices[char_vert_begin + 10] = glyph_uv_x_max;
    mesh_data.vertices[char_vert_begin + 11] = glyph_uv_y_max;
    // top-right
    mesh_data.vertices[char_vert_begin + 12] = glyph_pos_x + glyph_width;
    mesh_data.vertices[char_vert_begin + 13] = glyph_pos_y + glyph_height - glyph_max_height;
    mesh_data.vertices[char_vert_begin + 14] = glyph_uv_x_max;
    mesh_data.vertices[char_vert_begin + 15] = glyph_uv_y_base;
    // set element data of the current character box
    size_t char_index_begin = char_index * 6;
    // first triangle
    // NOTE: index is the index of char in text
    mesh_data.indices[char_index_begin + 0] = 0 + (GLuint)char_index * 4;
    mesh_data.indices[char_index_begin + 1] = 2 + (GLuint)char_index * 4;
    mesh_data.indices[char_index_begin + 2] = 1 + (GLuint)char_index * 4;
    // second triangle
    mesh_data.indices[char_index_begin + 3] = 0 + (GLuint)char_index * 4;
    mesh_data.indices[char_index_begin + 4] = 3 + (GLuint)char_index * 4;
    mesh_data.indices[char_index_begin + 5] = 2 + (GLuint)char_index * 4;
}