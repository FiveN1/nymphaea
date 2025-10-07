#include"pch.h"
#include"camera_3d.h"

void np_camera_3d_create(np_camera_3d* camera_3d) {
    glm_mat4_identity(camera_3d->view_matrix);
    np_tr3_create(&camera_3d->transform);
    // set direction
    glm_vec3_zero(camera_3d->direction);
    camera_3d->direction[2] = 1.0f; // face towards +Z axis
    // set up vector (up = Y axis)
    glm_vec3_zero(camera_3d->up);
    camera_3d->up[1] = 1.0f;
}

void np_camera_3d_delete(np_camera_3d* camera_3d) {
    
}

void np_camera_3d_update(np_camera_3d* camera_3d, int screen_width, int screen_height, float fov) {
    // create projection matrix
    mat4 projection_matrix;
    glm_perspective(glm_rad(fov), (float)screen_width / (float)screen_height, 0.1f, 100.0f, projection_matrix);


    //glm_perspective_default((float)screen_width / (float)screen_height, &projection_matrix);
    //float aspect = (float)screen_width / (float)screen_height;
    // set orthro matrix accordingly to aspect ratio
    //glm_ortho(-aspect, aspect, -1.0f, 1.0f, -1.0f, 1.0f, projection_matrix);
    
    // create lookat matrix
    mat4 lookat_matrix;
    vec3 center;
    glm_vec3_add(camera_3d->transform.position, camera_3d->direction, center);
    glm_lookat(camera_3d->transform.position, center, camera_3d->up, lookat_matrix);
    // set the final camera matrix
    glm_mat4_mul(projection_matrix, lookat_matrix, camera_3d->view_matrix);
    // TODO: set UP vector in camera adn custom fov

    // ...
    //glm_mat4_copy(projection_matrix, camera_3d->view_matrix);

}

mat4* np_camera_3d_get_matrix(np_camera_3d* camera_3d) {
    return &camera_3d->view_matrix;
}
