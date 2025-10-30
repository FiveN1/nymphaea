#include"pch.h"
#include"camera_2d.h"

void np_camera_2d_create(np_camera_2d* camera_2d) {
    np_tr2_create(&camera_2d->transform);
    // set zoom to {1.0f, 1.0f}
    glm_vec2_one(camera_2d->zoom);
}

void np_camera_2d_update(np_camera_2d* camera_2d, int screen_width, int screen_height) {
    // get aspect ratio
    float aspect = (float)screen_width / (float)screen_height;
    // set orthro matrix accordingly to aspect ratio
    glm_ortho(-aspect * camera_2d->zoom[0], aspect * camera_2d->zoom[0], -1.0f * camera_2d->zoom[1], 1.0f * camera_2d->zoom[1], -1.0f, 1.0f, camera_2d->view_matrix);
}

mat4* np_camera_2d_get_matrix(np_camera_2d* camera_2d) {
    return &camera_2d->view_matrix;
}

np_tr2* np_camera_2d_get_transform(np_camera_2d* camera_2d) {
    return &camera_2d->transform;
}