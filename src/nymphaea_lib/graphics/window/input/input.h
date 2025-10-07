#ifndef NP_WINDOW_INPUT_H
#define NP_WINDOW_INPUT_H

#include"nymphaea_lib/graphics/window/window.h"

// CALL IT INPUT

// check if a key is pressed
bool np_key_pressed(np_window* window, int key);
// check if a key is release
bool np_key_released(np_window* window, int key);
// check if a key is repeated
bool np_key_repeated(np_window* window, int key);
// check if mouse button pressed
bool np_mouse_button_pressed(np_window* window, int button);
// check if mouse button released
bool np_mouse_button_released(np_window* window, int button);

void np_get_mouse_position(np_window* window, double* mouse_x, double* mouse_y);
// vrátí normalizované souřadnice myši v okně (od -1.0 do 1.0)
void np_get_mouse_position_stretch(np_window* window, double* mouse_x, double* mouse_y);

#endif NP_WINDOW_INPUT_H