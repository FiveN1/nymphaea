#ifndef NP_RENDERER_H
#define NP_RENDERER_H

#include<Glad/glad.h>
#include<GLFW/glfw3.h>

// init Renderer (OpenGL, Vulkan, DirectX)
// init libraries? (glfw)


#define NP_OPENGL_VERSION_MAJOR 4
#define NP_OPENGL_VERSION_MINOR 6

void np_renderer_create();

void np_renderer_delete();


/*
* ## Změny:
*
* #### 30.05.2025 
* přidána funkce np_renderer_create(), np_renderer_delete()
*
*
*
*
*/

#endif NP_RENDERER_H