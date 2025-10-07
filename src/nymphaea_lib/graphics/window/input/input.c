#include"pch.h"
#include"input.h"

bool np_key_pressed(np_window* window, int key) {
	if (glfwGetKey(window->window, key) == GLFW_PRESS) return true;
	return false;
}

bool np_key_released(np_window* window, int key) {
	if (glfwGetKey(window->window, key) == GLFW_RELEASE) return true;
	return false;
}

bool np_key_repeated(np_window* window, int key) {
	if (glfwGetKey(window->window, key) == GLFW_REPEAT) return true;
	return false;
}

bool np_mouse_button_pressed(np_window* window, int button) {
	if (glfwGetMouseButton(window->window, button) == GLFW_PRESS) return true;
	return false;
}

bool np_mouse_button_released(np_window* window, int button) {
	if (glfwGetMouseButton(window->window, button) == GLFW_RELEASE) return true;
	return false;
}

void np_get_mouse_position(np_window* window, double* mouse_x, double* mouse_y) {
	glfwGetCursorPos(window->window, mouse_x, mouse_y);
	double aspect = (double)np_window_get_width(window) / (double)np_window_get_height(window);
	// normalize it so it is not dependent on window resolution
	// the smallest dimension is from -1.0 to 1.0
	if (aspect > 1.0) {
		*mouse_x = (*mouse_x * 2.0 / (double)np_window_get_width(window) - 1.0) * aspect;
		*mouse_y = *mouse_y * -2.0 / (double)np_window_get_height(window) + 1.0;
	} else {
		*mouse_x = *mouse_x * 2.0 / (double)np_window_get_width(window) - 1.0;
		*mouse_y = (*mouse_y * -2.0 / (double)np_window_get_height(window) + 1.0) * (1.0 / aspect);
	}
}

void np_get_mouse_position_stretch(np_window* window, double* mouse_x, double* mouse_y) {
	glfwGetCursorPos(window->window, mouse_x, mouse_y);
	*mouse_x = *mouse_x * 2.0 / (double)np_window_get_width(window) - 1.0;
	*mouse_y = *mouse_y * -2.0 / (double)np_window_get_height(window) + 1.0;
}