#include"camera.h"

void fractal_camera_create(fractal_camera* camera) {
    // set data
    camera->position_x = 0.0f;
    camera->position_y = 0.0f;
    camera->zoom = 5.0f;
}

void fractal_camera_update(fractal_camera* camera, np_window* window, double delta_time) {
    float speed = 0.001f;
    float zoom_speed = 0.001f;

    if (np_key_pressed(window, GLFW_KEY_W)) {
        camera->position_y += camera->zoom * delta_time * -speed;
    }
    if (np_key_pressed(window, GLFW_KEY_S)) {
        camera->position_y += camera->zoom * delta_time * speed;
    }

    if (np_key_pressed(window, GLFW_KEY_A)) {
        camera->position_x += camera->zoom * delta_time * -speed;
    }
    if (np_key_pressed(window, GLFW_KEY_D)) {
        camera->position_x += camera->zoom * delta_time * speed;
    }

    if (np_key_pressed(window, GLFW_KEY_Q)) {
        camera->zoom += camera->zoom * delta_time * zoom_speed;
    }
    if (np_key_pressed(window, GLFW_KEY_E)) {
        camera->zoom += camera->zoom * delta_time * -zoom_speed;
    }
}

void fractal_camera_on_event(fractal_camera* camera, np_event event, np_window* window) {
    
}