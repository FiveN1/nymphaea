#include"pch.h"
#include"freecam.h"


void np_freecam_create(np_freecam* freecam) {
    np_camera_3d_create(&freecam->camera);

    freecam->speed = 0.01f;
    freecam->sprint_speed = 0.1f;
    freecam->speed_state = freecam->speed;

    glm_vec2_zero(freecam->z_state);
    glm_vec2_zero(freecam->x_state);
    glm_vec2_zero(freecam->y_state);

    freecam->look_state = false;
}

void np_freecam_delete(np_freecam* freecam) {
    
}

void np_freecam_update(np_freecam* freecam, np_window* window, float fov) {
    // update camera position

    // forward movement vector
    vec3 forward_movement;
    glm_vec3_scale(freecam->camera.direction, (freecam->z_state[0] - freecam->z_state[1]) * freecam->speed_state, forward_movement);
    glm_vec3_add(freecam->camera.transform.position, forward_movement, freecam->camera.transform.position);
    // side movement vector
    vec3 side_movement;
    glm_cross(freecam->camera.direction, freecam->camera.up, side_movement);
    glm_normalize(side_movement);
    glm_vec3_scale(side_movement, (freecam->x_state[1] - freecam->x_state[0]) * freecam->speed_state, side_movement);
    glm_vec3_add(freecam->camera.transform.position, side_movement, freecam->camera.transform.position);
    // up movement vector
    vec3 up_movement;
    glm_vec3_scale(freecam->camera.up, (freecam->y_state[1] - freecam->y_state[0]) * freecam->speed_state, up_movement);
    glm_vec3_add(freecam->camera.transform.position, up_movement, freecam->camera.transform.position);

    // update camera rotation
    if (freecam->look_state) {
        // get cursor position 
        double mouse_x, mouse_y;
        glfwGetCursorPos(window->window, &mouse_x, &mouse_y);
        // by the cursor diffrence of position from original cursor position, get rotation value
        float camera_rotation_x = 1.0f * (float)(np_window_get_height(window) / 2 - mouse_y) / np_window_get_height(window);
        float camera_rotation_y = 1.0f * (float)(np_window_get_width(window) / 2 - mouse_x) / np_window_get_width(window);
        // get axis of x rotation
        vec3 axis;
        glm_cross(freecam->camera.direction, freecam->camera.up, axis);
        glm_normalize(axis);
        // rotate camera
        glm_vec3_rotate(freecam->camera.direction, camera_rotation_x, axis);
        glm_vec3_rotate(freecam->camera.direction, camera_rotation_y, freecam->camera.up);
        // reset cursor position
        glfwSetCursorPos(window->window, np_window_get_width(window) / 2, np_window_get_height(window) / 2);
    }
    // update camera matrix
    np_camera_3d_update(&freecam->camera, np_window_get_width(window), np_window_get_height(window), fov);
}

void np_freecam_on_event(np_freecam* freecam, np_event event, np_window* window) {
    
    if (event.type == NP_KEY_PRESS_EVENT) {
        // Z
        if (event.key_press_event.key == GLFW_KEY_W) {
            freecam->z_state[0] = 1.0f;
        }
        if (event.key_press_event.key == GLFW_KEY_S) {
            freecam->z_state[1] = 1.0f;
        }
        // X
        if (event.key_press_event.key == GLFW_KEY_A) {
            freecam->x_state[0] = 1.0f;
        }
        if (event.key_press_event.key == GLFW_KEY_D) {
            freecam->x_state[1] = 1.0f;
        }
        // Y
        if (event.key_press_event.key == GLFW_KEY_LEFT_CONTROL) {
            freecam->y_state[0] = 1.0f;
        }
        if (event.key_press_event.key == GLFW_KEY_SPACE) {
            freecam->y_state[1] = 1.0f;
        }
        // Sprint
        if (event.key_press_event.key == GLFW_KEY_LEFT_SHIFT) {
            freecam->speed_state = freecam->sprint_speed;
        }
        // look around
        if (event.key_press_event.key == GLFW_KEY_C) {
            // change look state
            freecam->look_state = !freecam->look_state;
            // when first clicked
            glfwSetCursorPos(window->window, np_window_get_width(window) / 2, np_window_get_height(window) / 2);
            // set cursor mode
            int cursor_mode = GLFW_CURSOR_NORMAL;
            if (freecam->look_state) cursor_mode = GLFW_CURSOR_DISABLED;
            glfwSetInputMode(window->window, GLFW_CURSOR, cursor_mode);
        }



    }

    if (event.type == NP_KEY_RELEASE_EVENT) {
        // Z
        if (event.key_press_event.key == GLFW_KEY_W) {
            freecam->z_state[0] = 0.0f;
        }
        if (event.key_press_event.key == GLFW_KEY_S) {
            freecam->z_state[1] = 0.0f;
        }
        // X
        if (event.key_press_event.key == GLFW_KEY_A) {
            freecam->x_state[0] = 0.0f;
        }
        if (event.key_press_event.key == GLFW_KEY_D) {
            freecam->x_state[1] = 0.0f;
        }
        // Y
        if (event.key_press_event.key == GLFW_KEY_LEFT_CONTROL) {
            freecam->y_state[0] = 0.0f;
        }
        if (event.key_press_event.key == GLFW_KEY_SPACE) {
            freecam->y_state[1] = 0.0f;
        }
        // Sprint
        if (event.key_press_event.key == GLFW_KEY_LEFT_SHIFT) {
            freecam->speed_state = freecam->speed;
        }
    }   
}

np_camera_3d* np_freecam_get_camera(np_freecam* freecam) {
    return &freecam->camera;
}