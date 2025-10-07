#include"pch.h"
#include"transform_2d.h"

void np_transform_2d_create(np_transform_2d* transform_2d) {
    glm_vec2_zero(transform_2d->position);
    transform_2d->orientation[0] = 1.0f;
    transform_2d->orientation[1] = 0.0f;
    glm_vec2_one(transform_2d->scale);
    // set empty matrix
    glm_mat3_identity(transform_2d->matrix);
}

void np_transform_2d_create_advanced(np_transform_2d* transform_2d, vec2 position, vec2 orientation, vec2 scale) {
    glm_vec2_copy(position, transform_2d->position);
    glm_vec2_copy(orientation, transform_2d->orientation);
    glm_vec2_copy(scale, transform_2d->scale);
    // set empty matrix
    glm_mat3_identity(transform_2d->matrix);
}

mat3* np_transform_2d_get(np_transform_2d* transform_2d) {
    // set matrix
    glm_mat3_identity(transform_2d->matrix);
    glm_translate2d(transform_2d->matrix, transform_2d->position);
    glm_scale2d(transform_2d->matrix, transform_2d->scale);
    // return matrix stored in the struct
    return &transform_2d->matrix;
}

void np_transform_2d_set_position(np_transform_2d* transform_2d, vec2 position) {
    glm_vec2_copy(position, transform_2d->position);
}

void np_transform_2d_set_orientation(np_transform_2d* transform_2d, vec2 orientation) {
    glm_vec2_copy(orientation, transform_2d->orientation);
}

void np_transform_2d_set_scale(np_transform_2d* transform_2d, vec2 scale) {
    glm_vec2_copy(scale, transform_2d->scale);
}