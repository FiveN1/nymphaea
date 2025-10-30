#include"camera.h"

void mbs_camera_create(mbs_camera* camera) {
    // set data
    camera->position_x = 0.0f;
    camera->position_y = 0.0f;
    camera->zoom = 5.0f;

    // create ssbo object.
    // will be updated every frame so we use GL_STREAM_DRAW
    //np_ssbo_create(&camera->ssbo, sizeof(mbs_camera_data), &camera->data, GL_STREAM_DRAW, ssbo_layout_index);
}

void mbs_camera_update(mbs_camera* camera, np_window* window, double delta_time) {
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

void mbs_camera_on_event(mbs_camera* camera, np_event event, np_window* window) {
    
}