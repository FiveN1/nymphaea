#include"pch.h"
#include"transform_2d.h"

void np_tr2_update_matrix(np_tr2* tr2) {
    glm_mat3_mul(tr2->transform_matrix, tr2->rotation_matrix, tr2->matrix);
    glm_mat3_mul(tr2->matrix, tr2->scale_matrix, tr2->matrix);

    // combine rotation and translation: https://lavalle.pl/vr/node80.html
    // je potřeba v mat4 !
}


void np_tr2_create(np_tr2* tr2) {
    // position
    glm_mat3_identity(tr2->transform_matrix);
    glm_vec2_zero(tr2->position);
    // rotation
    glm_mat3_identity(tr2->rotation_matrix);
    tr2->rotation = 0.0f;
    // scale
    glm_mat3_identity(tr2->scale_matrix);
    glm_vec2_zero(tr2->scale);
    // update matrix
    np_tr2_update_matrix(tr2);
}

void np_tr2_create_advanced(np_tr2* tr2, vec2 position, vec2 rotation, vec2 scale) {
    // position
    glm_mat3_identity(tr2->transform_matrix);
    glm_vec2_copy(position, tr2->position);
    // rotation
    glm_mat3_identity(tr2->rotation_matrix);
    glm_vec2_zero(rotation, tr2->rotation);
    // scale
    glm_mat3_identity(tr2->scale_matrix);
    glm_vec2_zero(scale, tr2->scale);
    // update matrix
    np_tr2_update_matrix(tr2);
}

mat3* np_tr2_get(np_tr2* tr2) {
    // return matrix stored in the struct
    return &tr2->matrix;
}

void np_tr2_set_position(np_tr2* tr2, vec2 position) {
    // set value
    glm_vec2_copy(position, tr2->position);
    // set matrix
    glm_mat3_identity(tr2->transform_matrix);
    glm_translate2d(tr2->transform_matrix, position);
    // update matrix
    np_tr2_update_matrix(tr2);
}

void np_tr2_set_rotation(np_tr2* tr2, float rotation) {
    // set value
    tr2->rotation = rotation;
    // set matrix
    glm_mat4_identity(tr2->rotation_matrix);
    glm_rotate2d(tr2->rotation_matrix, rotation);
    // update matrix
    np_tr2_update_matrix(tr2);
}

void np_tr2_set_scale(np_tr2* tr2, vec2 scale) {
    // set value
    glm_vec2_copy(scale, tr2->scale);
    // set matrix
    glm_mat3_identity(tr2->scale_matrix);
    glm_scale2d(tr2->scale_matrix, scale);
    // update matrix
    np_tr2_update_matrix(tr2);
}