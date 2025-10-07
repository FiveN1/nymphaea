#include"pch.h"
#include"point_light.h"

void np_point_light_create(np_point_light* point_light, np_scene* scene, vec3 color, vec3 position) {
    glm_vec3_copy(color, point_light->color);
    glm_vec3_copy(position, point_light->position);


    // přidat do scény...
}

void np_point_light_bind(np_point_light* point_light, const char* uniform_array, GLuint index) {
    // vytvoříme základní název pole v shaderu - "uniform_array[index]."
    // k tomuto poli budeme přidávat další componenty jelikož světlo na gpu je struct takže má různá data.
    /*
    char light_array_index[256];
    sprintf_s(light_array_index, 256, "%s[%u].", uniform_array, index);
    // do tohoto bufferu budem psát horní string + component structu.
    char full_uniform[256];

    sprintf_s(full_uniform, 256, "%s%s", light_array_index, "position");
    glUniform3fv(glGetUniformLocation(lightingShader.Program, full_uniform), 1, point_light->position);

    sprintf_s(full_uniform, 256, "%s%s", light_array_index, "ambient");
    glUniform3fv(glGetUniformLocation(lightingShader.Program, full_uniform), 1, point_light->color);
    */
}