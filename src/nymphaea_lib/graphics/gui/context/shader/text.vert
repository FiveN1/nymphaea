#version 460 core

layout (location = 0) in vec2 position;

layout (location = 1) in vec2 uv_in;

uniform mat3 model_matrix;
uniform mat3 view_matrix;
uniform mat4 proj_matrix;

out vec2 uv;

void main() {

	gl_Position = proj_matrix * vec4(view_matrix * model_matrix * vec3(position, 1.0f), 1.0f);

	uv = uv_in;
}