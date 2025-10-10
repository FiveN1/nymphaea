#include"pch.h"
#include"shader_program.h"
#include"nymphaea_lib/core/file/file/file.h"

np_shader_program np_shader_program_create(const GLchar* vertex_shader_source, const GLchar* geometry_shader_source, const GLchar* fragment_shader_source) {
    // compile status of the shader sources
    GLint status;
    GLuint has_geometry_shader = strlen(geometry_shader_source) != 0;
    
    // vertex shader
    
    // create vertex shader
    GLuint vertex_shader = glCreateShader(GL_VERTEX_SHADER);
    // compile the shader from the source code
    glShaderSource(vertex_shader, 1, &vertex_shader_source, NULL);
    glCompileShader(vertex_shader);
    // check for errors
    glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &status);
    np_assert(status, "VERTEX SHADER compilation error!");

    // geometry shader
    GLuint geometry_shader;
    if (has_geometry_shader) {
        geometry_shader = glCreateShader(GL_GEOMETRY_SHADER);
        // přidá geometry source code k shader objectu a compiluje ho
        glShaderSource(geometry_shader, 1, &geometry_shader_source, NULL);
        glCompileShader(geometry_shader);
        // Check
        glGetShaderiv(geometry_shader, GL_COMPILE_STATUS, &status);
        np_assert(status, "GEOMETRY SHADER compilation error!");
    }

    // fragment shader
    
    // create frgment shader
    GLuint fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
    fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
    // compile the shader from the source code
    glShaderSource(fragment_shader, 1, &fragment_shader_source, NULL);
    glCompileShader(fragment_shader);
    // check for errors
    glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &status);
    np_assert(status, "FRAGMENT SHADER compilation error!");

    // shader program
    
    // create shader program
    GLint shader_program = glCreateProgram();
    // attach shaders to program and link
    glAttachShader(shader_program, vertex_shader);
    if (has_geometry_shader) {
        glAttachShader(shader_program, geometry_shader);
    }
    glAttachShader(shader_program, fragment_shader);
    glLinkProgram(shader_program);
    // check for errors
    glGetProgramiv(shader_program, GL_LINK_STATUS, &status);
    if (!status) {
        GLchar* info_log = NULL;
        glGetProgramInfoLog(shader_program, 1024, NULL, info_log);
        np_assert(status, "SHADER PROGRAM link error!\nerror log: %s", info_log);
    }
    // delete the shaders since now they are in the program
    glDeleteShader(vertex_shader);
    if (has_geometry_shader) {
        glDeleteShader(geometry_shader);
    }
    glDeleteShader(fragment_shader);

    return shader_program;
}

np_shader_program np_shader_program_load(const char* vertex_shader_filename, const char* geometry_shader_filename, const char* fragment_shader_filename) {
    np_shader_program shader_program;
    // load the source code from a file
    char* vertex_shader_source = np_file_load_string(vertex_shader_filename);
    np_assert(vertex_shader_source != NULL, "SHADER PROGRAM ERROR: vertex shader file not found\n -> path: [%s] does not exist", vertex_shader_filename);
    
    char* geometry_shader_source = "";
    if (strlen(geometry_shader_filename) != 0) {
        geometry_shader_source = np_file_load_string(geometry_shader_filename);
        np_assert(vertex_shader_source != NULL, "SHADER PROGRAM ERROR: geometry shader file not found\n -> path: [%s] does not exist", geometry_shader_filename);
    }
    char* fragment_shader_source = np_file_load_string(fragment_shader_filename);
    np_assert(fragment_shader_source != NULL, "SHADER PROGRAM ERROR: fragment shader file not found\n -> path: [%s] does not exist", fragment_shader_filename);

    // create the shader program
    shader_program = np_shader_program_create(vertex_shader_source, geometry_shader_source, fragment_shader_source);
    // free the loaded shader source code when compiled
    np_file_free(vertex_shader_source);
    if (strlen(geometry_shader_filename) != 0) {
        np_file_free(geometry_shader_source);
    }
    np_file_free(fragment_shader_source);
    // return the id
    return shader_program;
}

void np_shader_program_delete(np_shader_program* shader_program) {
    glDeleteProgram(*shader_program);
    *shader_program = 0;
}

void np_shader_program_use(np_shader_program shader_program) {
    glUseProgram(shader_program);
}
