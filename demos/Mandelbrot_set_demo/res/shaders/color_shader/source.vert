#version 460 core
layout (location = 0) in vec2 position;

uniform mat3 model_matrix;
uniform mat3 view_matrix;
uniform mat4 proj_matrix;

void main() {
	gl_Position = proj_matrix * vec4(view_matrix * model_matrix * vec3(position, 1.0f), 1.0f);
}