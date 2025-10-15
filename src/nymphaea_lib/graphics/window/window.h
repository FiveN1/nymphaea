#ifndef NP_WINDOW_H
#define NP_WINDOW_H

#include"nymphaea_lib/graphics/renderer/renderer.h"
#include"event/event.h"

// event callback
typedef void(*np_event_callback)(np_event, void*);

/*
* window
* data about a window instance
*/
typedef struct np_window {
    // GLFW window pointer
    GLFWwindow* window;
    // size of window
    int width;
    int height;
    // program data pointer used in 'event_callback'
    void* program_data;
    // function pointer of functionction called on event
    np_event_callback event_callback;
} np_window;

// Create a window
void np_window_create(np_window* window, const void* program_data, int width, int height, const char* title);
// Close a window
void np_window_delete(np_window* window);
// update window buffers & poll events
// this shoud be the last function called in the main loop since it will display the new buffer on the screen.
void np_window_update(np_window* window);
// clear window buffer with color
void np_window_set_clear_color(float r, float g, float b, float a);
// clear window buffers !!!
void np_window_clear_buffers();
// close window
// changes the winow 'shoudClose' state to true.
void np_window_close(np_window* window);
// bind window callback.
// so when a window recieves an event the 'event_callback' function will be called.
// callback function (np_event event, void* data).
// - event holds data about an event.
// - data is the pointer to data passed at window creation.
// #### Parameters
// - np_window* window -> window instance
// - np_event_callback event_callback -> event callback function pointer.
void np_window_bind_event_callback(np_window* window, np_event_callback event_callback);
// enable or disable vsync.
// #### Parameters
// bool enabled -> state of vsync
void np_window_set_vsync(bool enabled);
// get window width (in pixels)
// #### Parameters
// np_window* window -> window instance
int np_window_get_width(np_window* window);
// get window height (in pixels)
// #### Parameters
// np_window* window -> window instance
int np_window_get_height(np_window* window);
// get GLFW window pointer
// #### Parameters
// np_window* window -> window instance
GLFWwindow* np_window_get_glfw_window(np_window* window);

//void np_window_set_cursor_position

// Key states vlastní file? (ANO)

// [01.06.2025] připojit framebuffer?
// - pro bars a pro filtry

/*
* Reference
* - GLFW window tutorial: https://www.glfw.org/docs/3.3/window_guide.html
* - GLAD wiki: https://www.khronos.org/opengl/wiki/OpenGL_Loading_Library
*/

/*
* Změny
* [27.05.2025] update názvů a zlepšení komentářů.
* [30.05.2025] odstranění OpenGL init funkcí z window_create a přenesení do renderer.h
* - Možná zařadit window.h do kategorie graphics/?
* [31.05.2025] přidáno np_window_get_glfw_window()
* [12.06.2025] přidána funkce keep aspekt při změne velikosti okna.
*
*
*/


#endif NP_WINDOW_H