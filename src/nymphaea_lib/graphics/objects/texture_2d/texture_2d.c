#include"pch.h"
#include"texture_2d.h"
#include"nymphaea_lib/core/file/image/image.h"

void np_texture_2d_create_from_file(np_texture_2d* texture_2d, GLenum format, GLenum filter, GLenum wrap, const char* filename) {
    // flip image on load
    np_image_flip_on_load(true);
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
    np_texture_2d_create(texture_2d, np_image_get_width(&image), np_image_get_height(&image), format, filter, wrap, image_format, np_image_get_data(&image));
    // delete the temporary image data once it is on the GPU
    np_image_delete(&image);
// debug
#ifdef NP_DEBUG_TEXTURE_2D
   np_debug_print("np_texture_2d: loaded texture from file \"%s\"", filename); 
#endif
}

void np_texture_2d_create(np_texture_2d* texture_2d, GLsizei width, GLsizei height, GLenum format, GLenum filter, GLenum wrap, GLenum pixles_format, const void* pixels) {
    glGenTextures(1, texture_2d);
    // set texture slot
    // https://stackoverflow.com/questions/14231391/what-is-the-function-of-glactivetexture-and-gl-texture0-in-opengl
    // https://stackoverflow.com/questions/8866904/differences-and-relationship-between-glactivetexture-and-glbindtexture
    glActiveTexture(GL_TEXTURE0);
    // set this texture as current
    glBindTexture(GL_TEXTURE_2D, *texture_2d);
    // set texture parameters
    // parameter doc: https://registry.khronos.org/OpenGL-Refpages/es2.0/xhtml/glTexParameter.xml
    // Set texture filtering for MINifying a MAGnigying
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filter);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filter);
    // set texture wrap parameter (S a T) = (X a Y)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrap);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrap);
    // set texture data
    // https://registry.khronos.org/OpenGL-Refpages/gl4/html/glTexImage2D.xhtml
    glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, pixles_format, GL_UNSIGNED_BYTE, pixels);
    // and unbind
    glBindTexture(GL_TEXTURE_2D, 0);

    np_debug_print("max texture objects: %i", GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS);
}

void np_texture_2d_create_empty(np_texture_2d* texture_2d, GLsizei width, GLsizei height, GLenum format, GLenum filter, GLenum wrap) {
    unsigned char* empty_pixels = (unsigned char*)malloc(width * height);
    memset(empty_pixels, 0, width * height);
    np_texture_2d_create(texture_2d, width, height, format, filter, wrap, GL_RED, empty_pixels); // will using GL_RED work? (for not allocating too many pixels)
    free(empty_pixels);
}

void np_texture_2d_delete(np_texture_2d* texture_2d) {
    glDeleteTextures(1, texture_2d);
    *texture_2d = 0;
}

void np_texture_2d_generate_mipmap(np_texture_2d* texture_2d) {
    glBindTexture(GL_TEXTURE_2D, *texture_2d);
    glGenerateMipmap(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 0);
}

void np_texture_2d_bind_sampler_unit(np_texture_2d texture_2d, np_shader_program shader_program, GLuint unit, const char* uniform_name) {
    // set current slot
    glActiveTexture(GL_TEXTURE0 + unit);
    // po volání této funkce se textura nabinduje na unit definovaný nahoře.
    glBindTexture(GL_TEXTURE_2D, texture_2d);
    // musíme také nastavit hodnotu uniformy.
    glUniform1i(glGetUniformLocation(shader_program, uniform_name), unit);
    // s shaderu uniforma drží hodnotu unitu.
    // proto musíme nastavit sampler unit pro každou uniformu - aby nebyly 2 textury na stejném unitu.
    // nemusí se volat každý frame. jenom když potřebuješ změnit slot.
}

void np_texture_2d_bind(np_texture_2d texture_2d) {
    glBindTexture(GL_TEXTURE_2D, texture_2d);
}

void np_texture_2d_unbind() {
    glBindTexture(GL_TEXTURE_2D, 0);
}

void np_texture_2d_set_pixels(np_texture_2d texture_2d, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, const void* pixels) {
    glBindTexture(GL_TEXTURE_2D, texture_2d);
    glTexSubImage2D(GL_TEXTURE_2D, 0, xoffset, yoffset, width, height, format, GL_UNSIGNED_BYTE, pixels);
    glBindTexture(GL_TEXTURE_2D, 0);
}