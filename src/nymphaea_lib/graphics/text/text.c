#include"pch.h"
#include"text.h"
#include"nymphaea_lib/core/data_structures/array/array.h"

void np_text_create_mesh(np_text* text, char* text_string);

void np_text_create(np_text* text, char* string, np_font* font, np_mesh* empty_mesh) {
    //
    // string content
    //
    // získáme délku textu
    text->string_length = strlen(string);
    // taky podle delku určíme velikost bufferu
    size_t string_buffer_size = sizeof(char) * (text->string_length + 1);
    // allocujem místo pro string.
    // z bezpečnostních důvodu je string kopírován jelikož originální zdroj může být deallocován.
    text->string = (char*)malloc(string_buffer_size);
    // nakonec zkopírujem string do bufferu
    strcpy_s(text->string, string_buffer_size, string);
    //
    // font
    //
    text->font = font;
    //
    // mesh
    //
    // mesh is created outside this function
    text->mesh = empty_mesh;
    // nastavíme text mesh attributy.
    // pozice: XY
    // texture: UV
    GLuint attributes[2] = {2, 2};
    // create mesh. mesh data will be set in the create_text_mesh() function
    np_mesh_create(text->mesh, (np_mesh_data){NULL, 0, NULL, 0, attributes, sizeof(attributes)});
    //
    // mesh vertices
    //
    // create vertex & element array that will be stored in CPU memory so we dont need to allocate large memory chunks when modyfying the text
    np_array_create(&text->verticies, 0, sizeof(GLfloat));
    np_array_create(&text->indices, 0, sizeof(GLuint));
    //
    // ostatní
    //
    text->width = 0.0f;
    text->height = 0.0f;
    //
    text->lines = 1;
    //
    // tvorba meshe
    //
    // set a mesh for the text
    np_text_create_mesh(text, string);
}

void np_text_delete(np_text* text) {
    free(text->string);
    text->string_length = 0;
    // delete text mesh
    // NOTE: the allocated space for the mesh needs to be freed outside (after) this function
    np_mesh_delete(text->mesh);
    text->mesh = NULL;
    // clear mesh buffer data
    np_array_delete(&text->verticies);
    np_array_delete(&text->indices);
}

void np_text_set(np_text* text, char* string) {
    // set text
    size_t string_length = strlen(string);
    size_t string_buffer_size = sizeof(char) * (string_length + 1);
    //
    if (string_length > text->string_length) {
        text->string_length = string_length;
        text->string = realloc(text->string, string_buffer_size);
    }
    strcpy_s(text->string, string_buffer_size, string);
    // create mesh
    np_text_create_mesh(text, string);
}

inline void np_text_set_glyph_mesh(np_glyph glyph, np_font* font, GLfloat* vertices, GLuint* indices, size_t index, GLfloat offset_x, GLfloat offset_y) {
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
    // top-left
    vertices[0] = glyph_pos_x;
    vertices[1] = glyph_pos_y + glyph_height - glyph_max_height;
    vertices[2] = glyph_uv_x_base;
    vertices[3] = glyph_uv_y_base;
    // bottom-left
    vertices[4] = glyph_pos_x;
    vertices[5] = glyph_pos_y - glyph_max_height;
    vertices[6] = glyph_uv_x_base;
    vertices[7] = glyph_uv_y_max;
    // bottom-right
    vertices[8] = glyph_pos_x + glyph_width;
    vertices[9] = glyph_pos_y - glyph_max_height;
    vertices[10] = glyph_uv_x_max;
    vertices[11] = glyph_uv_y_max;
    // top-right
    vertices[12] = glyph_pos_x + glyph_width;
    vertices[13] = glyph_pos_y + glyph_height - glyph_max_height;
    vertices[14] = glyph_uv_x_max;
    vertices[15] = glyph_uv_y_base;
    // set element data of the current character box
    // first triangle
    // NOTE: index is the index of char in text
    indices[0] = 0 + (GLuint)index * 4;
    indices[1] = 2 + (GLuint)index * 4;
    indices[2] = 1 + (GLuint)index * 4;
    // second triangle
    indices[3] = 0 + (GLuint)index * 4;
    indices[4] = 3 + (GLuint)index * 4;
    indices[5] = 2 + (GLuint)index * 4;
}

void np_text_create_mesh(np_text* text, char* text_string) {
    // number of characters in the text. (lenght of the text)
    size_t length = strlen(text_string);
    // resize if the text becomes longer
    if (np_array_get_size(&text->verticies) < length * 16) np_array_resize(&text->verticies, length * 16);
    if (np_array_get_size(&text->indices) < length * 6) np_array_resize(&text->indices, length * 6);
    // reset boundary
    text->width = 0.0f;
    text->height = 0.0f;
    // reset line amount
    text->lines = 1;
    // current text offset (like in a typewriter)
    GLfloat offset_x = 0.0f;
    GLfloat offset_y = 0.0f;
    // loop for ever char in text
    for (size_t i = 0; i < length; i++) {
        // change y offset if newline character encountered
        if (text_string[i] == '\n') {
            offset_x = 0.0f;
            offset_y -= np_font_get_row_offset(text->font);
            // also update line amount;
            text->lines++;
            continue;
        }
        // get glyph data
        np_glyph glyph = np_font_get_glyph(text->font, text_string[i]);
        // set mesh data for one glyph
        np_text_set_glyph_mesh(glyph, text->font, (GLfloat*)np_array_get(&text->verticies, i * 16), (GLuint*)np_array_get(&text->indices.data, i * 6), i, offset_x, offset_y);
        // update text boundary
        if (offset_x + glyph.advance_offset > text->width) text->width = offset_x + glyph.advance_offset;
        if (-offset_y + np_font_get_row_offset(text->font) > text->height) text->height = -offset_y + np_font_get_row_offset(text->font);
        // mone on to next char position
        offset_x += glyph.advance_offset;
    }
    // create the text mesh with the vertex & element data
    np_vbo_create_buffer(text->mesh->vbo, (GLfloat*)np_array_data(&text->verticies), (GLuint)np_array_get_size_bytes(&text->verticies), GL_DYNAMIC_DRAW);
    np_ebo_create_buffer(text->mesh->ebo, (GLfloat*)np_array_data(&text->indices), (GLuint)np_array_get_size_bytes(&text->indices), GL_DYNAMIC_DRAW);
    text->mesh->element_size = (GLuint)np_array_get_size(&text->indices);
}

GLfloat np_text_get_width(np_text* text) {
    return text->width;
}

GLfloat np_text_get_height(np_text* text) {
    return text->height;
}

np_mesh* np_text_get_mesh(np_text* text) {
    return text->mesh;
}

void np_text_set_font(np_text* text, np_font* font) {
    text->font = font;
}

char* np_text_get_string(np_text* text) {
    return text->string;
}

size_t np_text_get_index_by_position(np_text* text, float x, float y) {
    //np_log("%f", (float)floor(2.1f));
    // TODO: uložit počet řádků do np_text
    // SCETCHY

    // character origin position
    float x_offset = 0.0f;
    float y_offset = 0.0f;

    // TEST
    float glyph_height = (float)np_font_get_row_offset(text->font);
    // TEST
    if (y < -glyph_height * (float)text->lines) {
        y = -glyph_height * (float)text->lines;
    }

    // loop for every character in text and check for its rect
    for (size_t i = 0; i < strlen(text->string); i++) {
        // go to new line 
        if (text->string[i] == '\n') {
            // TEST pokud ale na tomto line byl point tak clamp
            if (y <= y_offset && y >= y_offset - glyph_height) {
                if (x >= x_offset) return i;
            }

            x_offset = 0.0f;
            y_offset -= (float)np_font_get_row_offset(text->font);
            continue;
        }
        // get glyph size
        np_glyph glyph = np_font_get_glyph(text->font, text->string[i]);
        float glpyh_width = (float)glyph.advance_offset;
        // check for point
        if (x >= x_offset && x <= x_offset + glpyh_width && y <= y_offset && y >= y_offset - glyph_height) {
            return i;
        }
        // move to next char
        x_offset += glpyh_width;
    }

    // TEST pokud ale na tomto line byl point tak clamp
    if (y <= y_offset && y >= y_offset - glyph_height) {
        if (x >= x_offset) return strlen(text->string);
    }



    

    // return invalid value
    return (size_t)-1;
}

size_t np_text_get_index_by_position_round(np_text* text, float x, float y) {

    np_glyph glyph = np_font_get_glyph(text->font, text->string[0]);

    // character origin position
    float x_offset = (float)glyph.advance_offset * 0.5f;
    float y_offset = 0.0f;
    // loop for every character in text and check for its rect
    for (size_t i = 1; i < strlen(text->string); i++) {
        // go to new line 
        if (text->string[i] == '\n') {
            x_offset = 0.0f;
            y_offset -= (float)np_font_get_row_offset(text->font);
            continue;
        }
        // get glyph size
        np_glyph glyph = np_font_get_glyph(text->font, text->string[i]);
        float glpyh_width = (float)glyph.advance_offset;
        float glyph_height = (float)np_font_get_row_offset(text->font);
        // check for point
        if (x > x_offset && x < x_offset + glpyh_width && y < y_offset && y > y_offset - glyph_height) {
            return i;
        }
        // move to next char
        x_offset += glpyh_width;
    }
    // return invalid value
    return (size_t)-1;
}

size_t np_text_get_position_by_index(np_text* text, size_t index, float* x, float* y) {
    size_t length = strlen(text->string);
    // return if index out of range
    if (index > length) return;
    // character position offset
    float x_offset = 0.0f;
    float y_offset = 0.0f;
    size_t row = 0;
    // loop for the whole text
    for (size_t i = 0; i < index; i++) {
        // go to new line 
        if (text->string[i] == '\n') {
            x_offset = 0.0f;
            y_offset -= (float)np_font_get_row_offset(text->font);
            row++;
            continue;
        }
        np_glyph glyph = np_font_get_glyph(text->font, text->string[i]);
        // move to next char
        x_offset += (float)glyph.advance_offset;
    }
    *x = x_offset;
    *y = y_offset;
    // the row position
    return row;
}

size_t np_text_get_index_by_position_clamp(np_text* text, float x, float y) {

    float glyph_height = (float)np_font_get_row_offset(text->font);

    // clamp to edge
    if (x < 0.0f) x = 0.0f; // tady jde udělat trik...
    if (y > 0.0f) y = 0.0f;

    // get line
    int line = (int)floor(-y / glyph_height);
    // pokud byl přesažen y limit, tak je vybrán pooslední line textu. tohle funguje jako clamp
    if (line >= text->lines) line = text->lines - 1;
    // find line index
    // (!!) pomalé, lze zlepšit pomocí držení hodnot nových lajen v array ale to zabere zbytečně moc místa a fragmentuje pamět.
    size_t line_begin;
    for (line_begin = 0; line_begin < strlen(text->string); line_begin++) {
        if (line == 0) break;
        if (text->string[line_begin] == '\n') line--;
    }
    // v vybraném line určit vybraný charakter.
    float x_offset = 0.0f;
    size_t i;
    for (i = line_begin; i < strlen(text->string); i++) {
        // go to new line 
        if (text->string[i] == '\n') {
            break;
        }
        // get glyph size
        np_glyph glyph = np_font_get_glyph(text->font, text->string[i]);
        float glpyh_width = (float)glyph.advance_offset;
        // check for point
        if (x >= x_offset && x <= x_offset + glpyh_width) {
            return i;
        }
        // move to next char
        x_offset += glpyh_width;
    }
    // pokud mimo rosah line tak je vrácen poslední index z line.
    return i;
}
