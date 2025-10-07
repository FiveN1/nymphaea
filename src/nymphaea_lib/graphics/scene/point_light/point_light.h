#ifndef NP_POINT_LIGHT_H
#define NP_POINT_LIGHT_H

#include"cglm/vec3-ext.h"
#include"cglm/mat4.h"
#include"cglm/cglm.h"

#include<nymphaea_lib/graphics/program/shader_program/shader_program.h>

#include<nymphaea_lib/graphics/scene/scene.h>

typedef struct np_point_light {
    vec3 color;
    vec3 position;
} np_point_light;

void np_point_light_create(np_point_light* point_light, np_scene* scene, vec3 color, vec3 position);

void np_point_light_bind(np_point_light* point_light, const char* uniform_array, GLuint index);


/*
* Změny
*
* [14.06.2025] vytvořeno - aby bylo možno snadno přidávat světla do scény.
*
*/

#endif NP_POINT_LIGHT_H