#include"pch.h"
#include"window.h"

// event init function that binds all of the GLFW event callbacks
void init_window_callback(GLFWwindow* window_instance);
// default event callback if not boud
void default_event_callback(np_event event, void* data);

void np_window_create(np_window* window, void* program_data, int width, int height, const char* title) {
	// set window size
    window->width = width;
    window->height = height;

	// set aspect ratio
	// used in window resize event
	window->aspect_ratio = (float)width / (float)height;

	// set window mode
	window->mode = NP_WINDOW_MODE_KEEP;

	// set program data
	// used in event callback
	window->program_data = program_data;

	// tohle asi nechat?
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, NP_OPENGL_VERSION_MAJOR);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, NP_OPENGL_VERSION_MINOR);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);

    // create window
    window->window = glfwCreateWindow(window->width, window->height, title, NULL, NULL);
	np_assert(window->window != NULL, "failed to create a window!");
    // create windows context
	glfwMakeContextCurrent(window->window);
	
	// init glad
	// tohle musí být načteno pro každý window context(?) 
	int opengl_version = gladLoadGL();
	np_assert(opengl_version != 0, "failed to load OpenGL");

	glViewport(0, 0, window->width, window->height);
	//glEnable(GL_BLEND);
	//glEnable(GL_DEPTH_TEST);	// Enables the Depth Buffer
	//glEnable(GL_CULL_FACE);		// Enables Cull Facing
	//glCullFace(GL_FRONT);		// Keeps front faces
	//glFrontFace(GL_CCW);		// Uses counter clock-wise standard
	//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); // set blend function

	// init events
	// set default event callback
	window->event_callback = &default_event_callback;
	// set GLFW window window pointer
	glfwSetWindowUserPointer(window->window, window);
	// init event callback from GLFW
	init_window_callback(window->window);
}

void np_window_delete(np_window* window) {
    glfwDestroyWindow(window->window);
    window->window = NULL;
}

void np_window_update(np_window* window) {
    glfwSwapBuffers(window->window);
	glfwPollEvents();
}

void np_window_set_clear_color(float r, float g, float b, float a) {
	glClearColor(r, g, b, a);
}

void np_window_clear_buffers() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT
}

void np_window_close(np_window* window) {
    glfwSetWindowShouldClose(window->window, true);
}

void np_window_set_vsync(bool enabled) {
	glfwSwapInterval(enabled);
}

void np_window_bind_event_callback(np_window* window, np_event_callback event_callback) {
	window->event_callback = event_callback;
}

int np_window_get_width(np_window* window) {
	return window->width;
}

int np_window_get_height(np_window* window) {
	return window->height;
}

GLFWwindow* np_window_get_glfw_window(np_window* window) {
	return window->window;
}

void np_widnow_set_mode(np_window* window, enum np_widnow_modes mode) {
	window->mode = mode;
}

//
// GLFW Event callbacks
//

// call event callback form window pointer with set parameters
void call_event(GLFWwindow* glfw_window, np_event event) {
	// get window pointer
	np_window* win_instance = (np_window*)glfwGetWindowUserPointer(glfw_window);
	// call callback function
	win_instance->event_callback(event, win_instance->program_data);
}

// key callback

void win_key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
	// set event data
	np_event event;
	// call event based on action
	switch (action) {
		// key press event
		case GLFW_PRESS:
			event.type = NP_KEY_PRESS_EVENT;
			event.key_press_event.key = key;
			break;
		// key release event
		case GLFW_RELEASE:
			event.type = NP_KEY_RELEASE_EVENT;
			event.key_release_event.key = key;
			break;
		// key repeat event
		case GLFW_REPEAT:
			event.type = NP_KEY_REPEAT_EVENT;
			event.key_repeat_event.key = key;
			break;
	}

	// debug
	#ifdef NP_WINDOW_DEBUG
	np_debug_print("np_window: key event: key %i",event.key_repeat_event.key);
	#endif

	// call event
	call_event(window, event);
}

// mouse callbacks

void win_cursor_position_callback(GLFWwindow* window, double xpos, double ypos) {
	np_window* win_instance = (np_window*)glfwGetWindowUserPointer(window);
	double aspect = (double)np_window_get_width(win_instance) / (double)np_window_get_height(win_instance);
	// set event data
	np_event event;
	event.type = NP_MOUSE_MOVE_EVENT;
	// normalize it so it is not dependent on window resolution
	// the smallest dimension is from -1.0 to 1.0
	if (aspect > 1.0) {
		event.mouse_move_event.xpos = (xpos * 2.0 / (double)np_window_get_width(win_instance) - 1.0) * aspect;
		event.mouse_move_event.ypos = ypos * -2.0 / (double)np_window_get_height(win_instance) + 1.0;
	} else {
		event.mouse_move_event.xpos = xpos * 2.0 / (double)np_window_get_width(win_instance) - 1.0;
		event.mouse_move_event.ypos = (ypos * -2.0 / (double)np_window_get_height(win_instance) + 1.0) * (1.0 / aspect);
	}

	// debug
	#ifdef NP_WINDOW_DEBUG
	np_debug_print("np_window: mouse move event: xpos %lf, ypos %lf", event.mouse_move_event.xpos, event.mouse_move_event.ypos);
	#endif

	// call event
	call_event(window, event);
}

void win_mouse_button_callback(GLFWwindow* window, int button, int action, int mods) {
	// set event data
	np_event event;
	event.type = NP_MOUSE_BUTTON_EVENT;
	event.mouse_button_event.button = button;
	event.mouse_button_event.action = action;
	event.mouse_button_event.mods = mods;

	// debug
	#ifdef NP_WINDOW_DEBUG
	np_debug_print("np_window: mouse button event: button %i, action %i, mods %i", event.mouse_button_event.button, event.mouse_button_event.action, event.mouse_button_event.mods);
	#endif

	// call event
	call_event(window, event);
}

void win_scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {
	// set event data
	np_event event;
	event.type = NP_MOUSE_SCROLL_EVENT;
	event.mouse_scroll_event.xoffset = xoffset;
	event.mouse_scroll_event.yoffset = yoffset;

	// debug
	#ifdef NP_WINDOW_DEBUG
	np_debug_print("np_window: mouse scroll event: xoffset %lf, yoffset %lf", event.mouse_scroll_event.xoffset, event.mouse_scroll_event.yoffset);
	#endif

	// call event
	call_event(window, event);
}

// window callbacks

void win_win_close_callback(GLFWwindow* window) {
	// set event data
	np_event event;
	event.type = NP_WINDOW_CLOSE_EVENT;

	// debug
	#ifdef NP_WINDOW_DEBUG
	np_debug_print("np_window: close event:");
	#endif

	// call event
	call_event(window, event);
}

void win_win_size_callback(GLFWwindow* window, int width, int height) {
	// set event data
	np_event event;
	event.type = NP_WINDOW_RESIZE_EVENT;
	event.window_resize_event.width = width;
	event.window_resize_event.height = height;
	// set window size
	np_window* win_instance = (np_window*)glfwGetWindowUserPointer(window);

	switch (win_instance->mode)
	{
	
		// strech
		case NP_WINDOW_MODE_STRETCH:
			win_instance->width = width;
			win_instance->height = height;
			// set viewport size
			glViewport(0, 0, width, height);
			break;
		
		// NP_WINDOW_MODE_KEEP
		// keep aspect ratio
		default:
			float aspect = (float)width / (float)height;
			//float og_aspect = 4.0f / 3.0f;
			if (aspect > 1.0f / win_instance->aspect_ratio) {
				win_instance->width = (int)((float)height * (win_instance->aspect_ratio));
				win_instance->height = height;
			} else {
				win_instance->width = width;
				win_instance->height = (int)((float)width * win_instance->aspect_ratio);
			}
			glViewport((width - win_instance->width) / 2, (height - win_instance->height) / 2, win_instance->width, win_instance->height);
			break;
	}

	// debug
	#ifdef NP_WINDOW_DEBUG
	np_debug_print("np_window: resize event: width %i, height %i", win_instance->width, win_instance->height);
	#endif

	// call event
	call_event(window, event);
	
}

void win_win_pos_callback(GLFWwindow* window, int xpos, int ypos) {
	// set event data
	np_event event;
	event.type = NP_WINDOW_MOVE_EVENT;
	event.window_move_event.xpos = xpos;
	event.window_move_event.ypos = ypos;

	// debug
	#ifdef NP_WINDOW_DEBUG
	np_debug_print("np_window: move event: xpos %i, ypos %i", event.window_move_event.xpos, event.window_move_event.ypos);
	#endif

	// call event
	call_event(window, event);
}

//
// GLFW Events
//

void init_window_callback(GLFWwindow* window_instance) {
	// bind key callback
	glfwSetKeyCallback(			window_instance, &win_key_callback);
	// bind mouse callbacks
	glfwSetCursorPosCallback(	window_instance, &win_cursor_position_callback);
	glfwSetMouseButtonCallback(	window_instance, &win_mouse_button_callback);
	glfwSetScrollCallback(		window_instance, &win_scroll_callback);
	// bind window callbacks
	glfwSetWindowCloseCallback(	window_instance, &win_win_close_callback);
	glfwSetWindowSizeCallback(	window_instance, &win_win_size_callback);
	glfwSetWindowPosCallback(	window_instance, &win_win_pos_callback);
	// GLFW event callback documentation: https://www.glfw.org/docs/3.2/input_guide.html
	// includes joystick callbacks
}

void default_event_callback(np_event event, void* data) {
	// nic se v callbacku neděje.

	// debug
	#ifdef NP_WINDOW_DEBUG
	np_debug_print_yellow("np_window: window event callback empty!");
	#endif
}