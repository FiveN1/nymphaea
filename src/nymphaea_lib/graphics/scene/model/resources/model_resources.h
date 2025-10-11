#ifndef NP_MODEL_RESOURCES_H
#define NP_MODEL_RESOURCES_H

#include"nymphaea_lib/graphics/program/shader_program/shader.h"


// vytvoří model shader z předem načteného shader source.
// * možná by bylo lepší načíst soubor při kompilaci do této funkce?
void np_model_resources_create_model_shader(np_shader* shader);

#endif NP_MODEL_RESOURCES_H