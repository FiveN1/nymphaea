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
*/
typedef struct np_tr2 {
    // transformation matrix. shoud not be accessed from this struct directly.
    mat4 matrix;
    // transform
    mat4 transform_matrix;
    vec3 position;
    // rotation
    mat4 rotation_matrix;
    float rotation; // nefunkční
    // scale
    mat4 scale_matrix;
    vec3 scale;
} np_tr2;

// create 2D transform
void np_tr2_create(np_tr2* tr2);
// create 2D transform but with all values set in this function
void np_tr2_create_advanced(np_tr2* tr2, vec2 position, vec2 rotation, vec2 scale);
// get 2D transformation matrix
// NOTE: when using this matrix in a shader to transform 2D coordinates, it has to be multiplied with vec3() with the last 'z' coordinate equal to 1.0
mat3* np_tr2_get(np_tr2* tr2);
// set 2D transform position
void np_tr2_set_position(np_tr2* tr2, vec2 position);
// set 2D transform orientation
void np_tr2_set_rotation(np_tr2* tr2, float rotation);
// set 2D transform scale
void np_tr2_set_scale(np_tr2* tr2, vec2 scale);

// TODO:
// dát jinam než do graphics/

/*
* Změny:
*
* [...]
* 
* [29.10.2025]
* přejmenováno na np_tr2 pro jednoduchost
* předělány všechny funkce, protože nebyly implementovány a nechápu jak mohli předtím fungovat :D
* teď je to všechno rozděleno do několika matrixů.
*
*/

#endif NP_TRANSFORM_2D_H