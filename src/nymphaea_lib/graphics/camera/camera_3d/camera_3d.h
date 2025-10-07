#ifndef NP_CAMERA_3D_H
#define NP_CAMERA_3D_H

#include"nymphaea_lib/graphics/transform/transform_3d/transform_3d.h"

/*
* ## Camera 3D
*
* Projector of data in your 3D world.
*
*/
typedef struct np_camera_3d {
    // the view matrix of the camera.
    // this matrix is safe to access anytime after calling 'np_camera_3d_update'
    mat4 view_matrix;
    // camera transform needed for creating the 'view_matrix'
    np_tr3 transform;
    //
    vec3 direction;
    vec3 up;
} np_camera_3d;

// create 3D camera
void np_camera_3d_create(np_camera_3d* camera_3d);
// update 3D camera
void np_camera_3d_update(np_camera_3d* camera_3d, int screen_width, int screen_height, float fov);
// get 3D camera view matrix
mat4* np_camera_3d_get_matrix(np_camera_3d* camera_3d);


/*
* [29.05.2025] přidán direction.
* - Aby nedocházelo k transformacím
* [30.05.2025] přidán camera movement struct
* [31.05.2025] odstraněn camera movement struct a přeměnen na np_freecam v freecam/freecam.h
*
*/

#endif NP_CAMERA_3D_H