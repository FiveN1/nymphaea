#include"pch.h"
#include"dsa_texture_2d.h"
#include"nymphaea_lib/core/file_system/image/image.h"

void np_dsa_texture_2d_create_from_file(np_dsa_texture_2d* dsa_texture_2d, GLenum format, GLenum filter, GLenum wrap, const char* filename) {
    // temporary image in cpu memory
    np_image image;
    // load the image
    np_image_load(&image, filename);
    // convert channels to GLenum
    GLenum image_format = GL_RGB;
    switch (np_image_get_channels(&image)) {
        case 1:
            image_format = GL_RED;
            break;
        case 2:
            image_format = GL_RG;
            break;
        case 3:
            image_format = GL_RGB;
            break;
        case 4:
            image_format = GL_RGBA;
            break;
    }
    // create the texture
    np_dsa_texture_2d_create(dsa_texture_2d, np_image_get_width(&image), np_image_get_height(&image), format, filter, wrap, image_format, np_image_get_data(&image));
    // delete the temporary image data once it is on the GPU
    np_image_delete(&image);
}

void np_dsa_texture_2d_create(np_dsa_texture_2d* dsa_texture_2d, GLuint width, GLuint height, GLenum format, GLenum filter, GLenum wrap, GLenum pixels_format, void* pixels) {
    // create empty texture
    np_dsa_texture_2d_create_empty(dsa_texture_2d, width, height, format, filter, wrap);
    // set image data
    glTextureSubImage2D(*dsa_texture_2d, 0, 0, 0, width, height, pixels_format, GL_UNSIGNED_BYTE, pixels);
}

void np_dsa_texture_2d_create_empty(np_dsa_texture_2d* dsa_texture_2d, GLuint width, GLuint height, GLenum format, GLenum filter, GLenum wrap) {
    // vytvoří texture objekt
    glCreateTextures(GL_TEXTURE_2D, 1, dsa_texture_2d);
    // Řekne opengl jak by mělo s texturamy pracovat
    // Nastaví filtrování textury pro zvětšování textury a zmenšování textury (MINifying a MAGnigying)
    glTextureParameteri(*dsa_texture_2d, GL_TEXTURE_MIN_FILTER, filter);
    glTextureParameteri(*dsa_texture_2d, GL_TEXTURE_MAG_FILTER, filter);
    // Nastaví parametry textury (S a T) = (X a Y)
    glTextureParameteri(*dsa_texture_2d, GL_TEXTURE_WRAP_S, wrap);
    glTextureParameteri(*dsa_texture_2d, GL_TEXTURE_WRAP_T, wrap);
    // set texture data
    glTextureStorage2D(*dsa_texture_2d, 1, format, width, height);

    // NP_DEBUG_DSA_TEXTURE_2D

    np_dsa_texture_2d_generate_mipmap(*dsa_texture_2d);
}

void np_dsa_texture_2d_delete(np_dsa_texture_2d* dsa_texture_2d) {
    glDeleteTextures(1, dsa_texture_2d);
    *dsa_texture_2d = 0;
}

void np_dsa_texture_2d_generate_mipmap(np_dsa_texture_2d dsa_texture_2d) {
    glGenerateTextureMipmap(dsa_texture_2d);
}

void np_dsa_texture_2d_bind_sampler_unit(np_dsa_texture_2d dsa_texture_2d, np_shader_program shader_program, GLuint unit, char* uniform_name) {
    glBindTextureUnit(unit, dsa_texture_2d);
    glUniform1i(glGetUniformLocation(shader_program, uniform_name), 0);
}

void np_dsa_texture_2d_bind_layout_unit(np_dsa_texture_2d dsa_texture_2d, GLuint unit, GLenum access, GLenum format) {
    glBindImageTexture(unit, dsa_texture_2d, 0, GL_FALSE, 0, access, format);
}