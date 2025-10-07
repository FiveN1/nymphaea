#include"pch.h"
#include"renderer.h"

void np_renderer_create() {
    // init OpenGL renderer
    // initilize GLFW
    np_assert(glfwInit() != GLFW_FALSE, "np_renerer: failed to load GLFW");
}

void np_renderer_delete() {
    glfwTerminate();
}