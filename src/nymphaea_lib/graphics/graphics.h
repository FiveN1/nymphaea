#ifndef NP_GRAPHICS_H
#define NP_GRAPHICS_H

/*
* Nymphaea🌸 Graphics
*
* Canvas and the Paint
* In Nymphaea you have 2 types of graphical objects.
* The canvas and the paint. with this you can do anything.
* The canvas is a space where you will paint your graphics.
* The paint is what you use to draw the graphics. (With a shader)
*
*/

// objects
#include"objects/vbo/vbo.h"
#include"objects/ebo/ebo.h"
#include"objects/vao/vao.h"
#include"objects/ssbo/ssbo.h"
#include"objects/fbo/fbo.h"
#include"objects/rbo/rbo.h"
#include"objects/texture_2d/texture_2d.h"
#include"objects/dsa_texture_2d/dsa_texture_2d.h"

// programs / shaders
#include"objects/shader_program/shader_program.h"
#include"objects/compute_program/compute_program.h"

// the canvas
#include"mesh/mesh.h"

// transforms
#include"transform/transform_2d/transform_2d.h"
#include"transform/transform_3d/transform_3d.h"

// camera
#include"camera/camera_2d/camera_2d.h"
#include"camera/camera_3d/camera_3d.h"

// high-level
#include"font/font.h"
#include"text/text.h"
#include"framebuffer/framebuffer.h"

#include"text/text_2d/text_2d.h"

#include"text/text_highlight/text_highlight.h"

// Graphics User Interface
//#include"gui/npgui.h"
#include"gui/gui.h"


//
// UNDER CONSTRUCTION
//

#include"camera/camera_2d/camera_2d.h"

#endif NP_GRAPHICS_H