#include"pch.h"
#include"compute_program.h"
#include"nymphaea_lib/core/file/file/file.h"

void np_compute_program_create(np_compute_program* compute_program, const char* compute_shader_source) {
    GLint success;
    // <COMPUTE SHADER> //
    // vytvoří compute shader objekt
    GLuint compute_shader = glCreateShader(GL_COMPUTE_SHADER);
    // přidá compute source code k shader objectu a compiluje ho
    glShaderSource(compute_shader, 1, &compute_shader_source, 0);
    glCompileShader(compute_shader);
    // compilation status check
    glGetShaderiv(compute_shader, GL_COMPILE_STATUS, &success);
    np_assert(success, "COMPUTE SHADER compilation error!");
    // <SHADER PROGRAM> //
    // Vytvoří Shader program
    *compute_program = glCreateProgram();
    // Přidá compilnute shadery do programu a linkne je
    glAttachShader(*compute_program, compute_shader);
    glLinkProgram(*compute_program);
    // Smaže shadery protože je už nepotřebujem
    glDeleteShader(compute_shader);
}

void np_compute_program_load(np_compute_program* compute_program, const char* compute_shader_source_dir) {
    char* compute_shader_source = np_file_load_string(compute_shader_source_dir);
    np_compute_program_create(compute_program, compute_shader_source);
    np_file_free(compute_shader_source);
}

void np_compute_program_delete(np_compute_program* compute_program) {
    glDeleteProgram(*compute_program);
    *compute_program = 0;
}

void np_compute_program_use(np_compute_program compute_program, GLuint num_groups_x, GLuint num_groups_y, GLuint num_groups_z) {
    glUseProgram(compute_program);
    glDispatchCompute(num_groups_x, num_groups_y, num_groups_z);
    glMemoryBarrier(GL_ALL_BARRIER_BITS);
}