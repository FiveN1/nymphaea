#ifndef NP_TRANSFORM_3D_H
#define NP_TRANSFORM_3D_H

#include"cglm/vec3-ext.h"
#include"cglm/mat4.h"
#include"cglm/cglm.h"

/*
* ## Transform 3D
*
* Used for transforming 3D verticies.
* Any vertex or collection of 3D verticies can by moved, rotated or scaled by this transform.
*
* NOTE: změna hodnot pozice přímo z struct nemění matrix takže nedojde k žádným transformacím.
*/
typedef struct np_tr3 {
    // transformation matrix. shoud not be accessed from this struct directly.
    mat4 matrix;
    // transform
    mat4 transform_matrix;
    vec3 position;
    // rotation
    mat4 rotation_matrix;
    vec3 rotation;
    // scale
    mat4 scale_matrix;
    vec3 scale;
} np_tr3;

// create 3D transform
void np_tr3_create(np_tr3* tr3);
// create 3D transform but with all values set in this function
void np_tr3_create_advanced(np_tr3* tr3, vec3 position, vec3 orientation, vec3 scale);
// get 3D transformation matrix
mat4* np_tr3_get(np_tr3* tr3);
// nastav pozici 3D Transformu 
// #### Parameters
// - np_tr3* tr3 -> instance transformu 3D.
// - vec3 position -> hodnoty nové pozice.
void np_tr3_set_position(np_tr3* tr3, vec3 position);
// nastav rotaci transformu.
// #### Parameters
// - np_tr3* tr3 -> instance transformu 3D.
// - vec3 rotation -> nová rotace
void np_tr3_set_rotation(np_tr3* tr3, vec3 rotation);
// nastav scale transformu.
// #### Parameters
// - np_tr3* tr3 -> instance transformu 3D.
void np_tr3_set_scale(np_tr3* tr3, vec3 scale);


/*
* [29.05.2025] přidán rotation matrix, pro možnost transformace směru.
* - Možná transform bude jenom matrix? Tento matrix pak bude transformován pouze glm_ funkcemi. +jednoduchost +flexibilita.
* - nebo bude lepší to rozdělit na 3 matrixy, (translation, rotation, scale) +rychlost, +jednoduchost.
* [04.06.2025] po odebrání znovu přidán rotation matrix i další matrixy (transform, scale) pro jednoduchost posílání uniforem.
* - v materiálu všechny transformy budou v jenom mat4* poli takže tohle je lepší metoda.
* - přejmenováno na np_tr3 z np_transform_3d, z důvodu složitého názvu.
*/


#endif NP_TRANSFORM_3D_H