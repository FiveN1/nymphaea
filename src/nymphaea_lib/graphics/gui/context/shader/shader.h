#ifndef NP_GUI_DEFAULT_SHADER_H
#define NP_GUI_DEFAULT_SHADER_H

#include"nymphaea_lib/graphics/font/font.h"
#include"nymphaea_lib/graphics/objects/shader_program/shader_program.h"
#include"nymphaea_lib/graphics/transform/transform_2d/transform_2d.h"
#include"nymphaea_lib/graphics/mesh/mesh.h"
#include"nymphaea_lib/graphics/camera/camera_2d/camera_2d.h"


//
// flat color shader
//

typedef struct np_gui_color_shader_data {
    vec4 color;
    np_transform_2d* text_transform;
    np_camera_2d* camera_2d;
} np_gui_color_shader_data;

void np_gui_color_shader_use(np_mesh* mesh, np_shader_program shader_program, np_gui_color_shader_data* data);

//
// text shader
//

typedef struct np_gui_text_shader_data {
    np_texture_2d font_atlas;
    np_transform_2d* text_transform;
    np_camera_2d* camera_2d;
} np_gui_text_shader_data;

void np_gui_text_shader_use(np_mesh* mesh, np_shader_program shader_program, np_gui_text_shader_data* data);


// nejakej hlavní shader context?
// všechny shadery tam budou...


#endif NP_GUI_DEFAULT_SHADER_H