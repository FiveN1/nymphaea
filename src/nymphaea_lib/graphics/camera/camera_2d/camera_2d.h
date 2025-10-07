#ifndef NP_CAMERA_2D_H
#define NP_CAMERA_2D_H

#include"nymphaea_lib/graphics/transform/transform_2d/transform_2d.h"

/*
* Camera 2D
*
* Projector of data in your 2D world.
*
*
*/
typedef struct np_camera_2d {
    mat4 view_matrix;
    np_transform_2d transform;
    // zoom can be 2-dimensional
    // zoom a trnsform scale jsou jiné věci.
    // - zoom zvětšuje objekty relativně ke kameře.
    // - scale zvětšuje samostatné objekty.
    vec2 zoom;
    // vec2 direction
} np_camera_2d;

// create 2D camera
void np_camera_2d_create(np_camera_2d* camera_2d);
// update 2D camera
void np_camera_2d_update(np_camera_2d* camera_2d, int screen_width, int screen_height);
// get view matrix of camera
mat4* np_camera_2d_get_matrix(np_camera_2d* camera_2d);

np_transform_2d* np_camera_2d_get_transform(np_camera_2d* camera_2d);

#endif NP_CAMERA_2D_H