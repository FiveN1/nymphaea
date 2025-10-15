#include"pch.h"
#include"image.h"
// use of stb functions once and for all
#define STB_IMAGE_IMPLEMENTATION
// !! NOTE: The stb image header can only be included once !!
#include<stb/stb_image.h>

void np_image_load(np_image* image, const char* filename){
    image->image_data = stbi_load(filename, &image->width, &image->height, &image->channels, 0);
    np_assert(image->image_data != NULL, "failed to load image from:\n -> %s", filename);
}

void np_image_delete(np_image* image) {
    // deallocate image data
    stbi_image_free(image->image_data);
    image->image_data = NULL;
    // set other variables to null
    image->width = 0;
    image->height = 0;
    image->channels = 0;
}

void np_image_flip_on_load(bool shoud_flip) {
    stbi_set_flip_vertically_on_load(shoud_flip);
}

unsigned char* np_image_get_data(np_image* image) {
    return image->image_data;
}

int np_image_get_width(np_image* image) {
    return image->width;
}

int np_image_get_height(np_image* image) {
    return image->height;
}

int np_image_get_channels(np_image* image) {
    return image->channels;
}