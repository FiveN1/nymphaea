#include"pch.h"
#include"transform_3d.h"

void np_tr3_update_matrix(np_tr3* tr3) {
    glm_mat4_mul(tr3->transform_matrix, tr3->rotation_matrix, tr3->matrix);
    glm_mat4_mul(tr3->matrix, tr3->scale_matrix, tr3->matrix);
}


void np_tr3_create(np_tr3* tr3) {
    // každý typ transformace je rozdělen do svých metrixů.
    // hodntoy jsou používány pro získání transformace.
    // position 
    glm_mat4_identity(tr3->transform_matrix);
    glm_vec3_zero(tr3->position);
    // rotation
    glm_mat4_identity(tr3->rotation_matrix);
    glm_vec3_zero(tr3->rotation);
    // scale
    glm_mat4_identity(tr3->scale_matrix);
    glm_vec3_zero(tr3->scale);
}

void np_tr3_create_advanced(np_tr3* tr3, vec3 position, vec3 rotation, vec3 scale) {
    //glm_vec3_copy(position, tr3->position);
    //glm_vec3_copy(rotation, tr3->rotation);
    //glm_vec3_copy(scale, tr3->scale);
}

mat4* np_tr3_get(np_tr3* tr3) {
    // zkombinujem všechny matrixy do jednoho
    np_tr3_update_matrix(tr3);
    // return matrix stored in the struct
    return &tr3->matrix;
}

void np_tr3_set_position(np_tr3* tr3, vec3 position) {
    glm_vec3_copy(position, tr3->position);
    // set matrix
    glm_mat4_identity(tr3->transform_matrix);
    glm_translate(tr3->transform_matrix, position);

    np_tr3_update_matrix(tr3);
}

void np_tr3_set_rotation(np_tr3* tr3, vec3 rotation) {
    glm_vec3_copy(rotation, tr3->rotation);
    // set matrix
    glm_mat4_identity(tr3->rotation_matrix);
    glm_rotate(tr3->rotation_matrix, rotation[0], (vec3){1.0f, 0.0f, 0.0f});
    glm_rotate(tr3->rotation_matrix, rotation[1], (vec3){0.0f, 1.0f, 0.0f});
    glm_rotate(tr3->rotation_matrix, rotation[2], (vec3){0.0f, 0.0f, 1.0f});

    np_tr3_update_matrix(tr3);
}

void np_tr3_set_scale(np_tr3* tr3, vec3 scale) {
    glm_vec3_copy(scale, tr3->scale);
    // set matrix
    glm_mat4_identity(tr3->scale_matrix);
    glm_scale(tr3->scale_matrix, scale);

    np_tr3_update_matrix(tr3);
}