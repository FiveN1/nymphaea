#include"pch.h"
#include"text_highlight.h"

// some |6text|10 here

/*
void np_text_highlight_create(np_text_highlight* text_highlight, np_text_2d* text_2d, np_mesh* empty_mesh) {
    // create transform
    np_transform_2d_create(&text_highlight->transform);
    glm_vec2_copy(text_2d->transform_2d.position, text_highlight->transform.position);
    
    // create mesh
    //np_mesh_create(text_highlight->mesh, );

}
*/

void np_text_highlight_create(np_text_highlight* text_highlight, np_mesh* empty_mesh) {
    // set mesh address
    text_highlight->mesh = empty_mesh;
    // create attribute array
    np_array attributes;
    np_array_create(&attributes, 1, sizeof(GLuint));
    ((GLuint*)np_array_data(&attributes))[0] = 2;
    // create empty mesh
    np_mesh_create(text_highlight->mesh, (np_mesh_data){NULL, 0, NULL, 0, (GLuint*)np_array_data(&attributes), np_array_get_size_bytes(&attributes)});
    np_array_delete(&attributes);
    // create vertex and element arrays
    np_array_create(&text_highlight->vertices, 0, sizeof(GLfloat));
    np_array_create(&text_highlight->indices, 0, sizeof(GLuint));
    // create transform
    np_transform_2d_create(&text_highlight->transform);
}

void np_text_highlight_set(np_text_highlight* text_highlight, np_text* text, size_t begin, size_t end) {

    float begin_x, begin_y;
    float end_x, end_y;
    // z techto return value budem znát kolik je potřeba allocovat místa pro mesh data, jelikož každý row potřebuje 4 vertexy
    size_t i1 = np_text_get_position_by_index(text, begin, &begin_x, &begin_y);
    size_t i2 = np_text_get_position_by_index(text, end, &end_x, &end_y);

    // resize array
    if (np_array_get_size(&text_highlight->vertices) < 4 * 2) np_array_resize(&text_highlight->vertices, 4 * 2); 
    if (np_array_get_size(&text_highlight->indices) < 6) np_array_resize(&text_highlight->indices, 6); 


    GLfloat* vertices = (GLfloat*)np_array_data(&text_highlight->vertices);
    GLuint* indices = (GLuint*)np_array_data(&text_highlight->indices);
    
    // top left
    vertices[0] = begin_x;
    vertices[1] = begin_y;
    // bottom left
    vertices[2] = begin_x;
    vertices[3] = end_y - np_font_get_row_offset(text->font);
    // bottom right
    vertices[4] = end_x;
    vertices[5] = end_y - np_font_get_row_offset(text->font);
    // top right
    vertices[6] = end_x;
    vertices[7] = begin_y;
    

    indices[0] = 0;
    indices[1] = 2;
    indices[2] = 1;

    indices[3] = 0;
    indices[4] = 3;
    indices[5] = 2;


    np_vbo_create_buffer(text_highlight->mesh->vbo, (GLfloat*)np_array_data(&text_highlight->vertices), (GLuint)np_array_get_size_bytes(&text_highlight->vertices), GL_DYNAMIC_DRAW);
    np_ebo_create_buffer(text_highlight->mesh->ebo, (GLuint*)np_array_data(&text_highlight->indices), (GLuint)np_array_get_size_bytes(&text_highlight->indices), GL_DYNAMIC_DRAW);
    text_highlight->mesh->element_size = (GLuint)np_array_get_size(&text_highlight->indices);


    // create mesh data

    /*
    GLfloat* vertices = (GLfloat*)np_array_data(&text_highlight->vertices);
    GLuint* indices = (GLuint*)np_array_data(&text_highlight->indices);


    vertices[0] = 0.0f;
    vertices[1] = 0.0f;

    vertices[0] = 1.0f;
    vertices[1] = 0.0f;

    vertices[0] = 1.0f;
    vertices[1] = 1.0f;

    indices[0] = 0;
    indices[1] = 1;
    indices[2] = 2;

    // set mesh data
    np_vbo_create_buffer(text_highlight->mesh->vbo, (GLfloat*)np_array_data(&text_highlight->vertices), (GLuint)np_array_get_size_bytes(&text_highlight->vertices), GL_DYNAMIC_DRAW);
    np_ebo_create_buffer(text_highlight->mesh->ebo, (GLuint*)np_array_data(&text_highlight->indices), (GLuint)np_array_get_size_bytes(&text_highlight->indices), GL_DYNAMIC_DRAW);
    text_highlight->mesh->element_size = (GLuint)np_array_get_size(&text_highlight->indices);
    */

    //np_mesh_data buffer_data = np_mesh_procedural_rectangle(0.1f, np_font_get_row_offset(text->font));
    //np_vbo_create_buffer(text_highlight->mesh->vbo, buffer_data.vertices, buffer_data.verticies_size, GL_DYNAMIC_DRAW);
    //np_ebo_create_buffer(text_highlight->mesh->ebo, buffer_data.indices, buffer_data.indices_size, GL_DYNAMIC_DRAW);
    //text_highlight->mesh->element_size = buffer_data.indices_size / sizeof(GLuint);
    //np_mesh_data_free(buffer_data);
    
}

size_t np_text_highlight_get_index_by_position(np_text* text, float x, float y, float* char_x, float* char_y) {
    // character origin position
    float x_offset = 0.0f;
    float y_offset = 0.0f;
    // loop for every character in text and check for its rect
    for (size_t i = 0; i < strlen(text->string); i++) {
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
            if (char_x != NULL) *char_x = x_offset;
            if (char_y != NULL) *char_y = y_offset;
            return i;
        }
        // move to next char
        x_offset += glpyh_width;
    }
    // return invalid value
    return (size_t)-1;
}

void np_text_highlight_on_event(np_text_highlight* text_highlight, np_text* text, np_event event) {

}