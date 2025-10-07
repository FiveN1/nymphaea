#ifndef NP_TRANSFORM_2D_H
#define NP_TRANSFORM_2D_H

#include"cglm/vec2-ext.h"
#include"cglm/mat4.h"
#include"cglm/cglm.h"
#include"cglm/mat3.h"

/*
* ## Transform 2D
* 
* Used for transforming 2D verticies.
* Any vertex or collection of 2D verticies can by moved, rotated or scaled by this transform.
*
* ## Related Functions
* - np_transform_2d_create
* - np_transform_2d_create_advanced
* - np_transform_2d_get
* - np_transform_2d_set_position
* - np_transform_2d_set_orientation
* - np_transform_2d_set_scale
*/
typedef struct np_transform_2d {
    // transformation variables by wich the matrix is transformed
    vec2 position;
    vec2 orientation;
    vec2 scale;
    // transformation matrix. shoud not be accessed from this struct directly.
    mat3 matrix;
} np_transform_2d;

// create 2D transform
void np_transform_2d_create(np_transform_2d* transform_2d);
// create 2D transform but with all values set in this function
void np_transform_2d_create_advanced(np_transform_2d* transform_2d, vec2 position, vec2 orientation, vec2 scale);
// get 2D transformation matrix
// NOTE: when using this matrix in a shader to transform 2D coordinates, it has to be multiplied with vec3() with the last 'z' coordinate equal to 1.0
mat3* np_transform_2d_get(np_transform_2d* transform_2d);
// set 2D transform position
void np_transform_2d_set_position(np_transform_2d* transform_2d, vec2 position);
// set 2D transform orientation
void np_transform_2d_set_orientation(np_transform_2d* transform_2d, vec2 orientation);
// set 2D transform scale
void np_transform_2d_set_scale(np_transform_2d* transform_2d, vec2 scale);

#endif NP_TRANSFORM_2D_H