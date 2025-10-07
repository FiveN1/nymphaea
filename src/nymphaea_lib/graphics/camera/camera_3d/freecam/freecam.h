#ifndef NP_FREECAM_H
#define NP_FREECAM_H

#include"nymphaea_lib/graphics/camera/camera_3d/camera_3d.h"
#include"nymphaea_lib/core/event/event.h"
#include"nymphaea_lib/graphics/window/window.h" // zahrnuto kvůli GLFW knihovně.
#include"nymphaea_lib/graphics/window/input/input.h"

/*
* ## Freecam
* 3D camera s možností volného pohybu.
* Skvělé pro testování 3D scén.
* 
*
*/
typedef struct np_freecam {
    // camera 3D instance
    np_camera_3d camera;
    // freecam speed
    float speed;
    float sprint_speed;
    // cameras state values
    // used to store key states using the event system
    // current speed
    float speed_state;
    // holds info about cameras forward and backward movement (X = forward, Y = backward)
    vec2 z_state;
    vec2 x_state;
    vec2 y_state;

    bool look_state;
} np_freecam;

// create freecam
// #### Parameters
// - np_freecam* freecam -> freecam instance
void np_freecam_create(np_freecam* freecam);
// delete freecam data
// #### Parameters
// - np_freecam* freecam -> freecam instance
void np_freecam_delete(np_freecam* freecam);
// update freecam (its matrix) every frame
// #### Parameters
// - np_freecam* freecam -> freecam instance
// - int screen_width -> width of screen, used to get the aspect ratio
// - int screen_height -> height of screen, used to get the aspect ratio
// - float fov -> cameras field of view in degrees
void np_freecam_update(np_freecam* freecam, np_window* window, float fov);
// update camera states when an event happens, like a keyboard press to move camera forward.
// #### Parameters
// - np_freecam* freecam -> freecam instance
// - np_event event -> data about the event
void np_freecam_on_event(np_freecam* freecam, np_event event, np_window* window);
// get freecams camera_3d
// #### Parameters
// - np_freecam* freecam -> freecam instance
np_camera_3d* np_freecam_get_camera(np_freecam* freecam);



/*
* [31.05.2025] vytvořeno
*
*
*
*
*
*/

#endif NP_FREECAM_H