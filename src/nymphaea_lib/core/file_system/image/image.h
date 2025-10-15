#ifndef NP_IMAGE_H
#define NP_IMAGE_H

/*
* image.h
*
* functions for image file manipulation using the stb image library
*
*/

typedef struct np_image {
    unsigned char* image_data;
    int width;
    int height;
    int channels;
} np_image;

// load image file with the stb library
void np_image_load(np_image* image, const char* filename);
// delete loaded image
void np_image_delete(np_image* image);

void np_image_flip_on_load(bool shoud_flip);

unsigned char* np_image_get_data(np_image* image);

int np_image_get_width(np_image* image);

int np_image_get_height(np_image* image);

int np_image_get_channels(np_image* image);

#endif NP_IMAGE_H
