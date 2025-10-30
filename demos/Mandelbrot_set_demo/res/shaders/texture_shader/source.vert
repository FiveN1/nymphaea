#version 460 core
layout (location = 0) in vec2 position;
layout (location = 1) in vec2 in_uv;

uniform mat3 model_matrix;
uniform mat3 view_matrix;
uniform mat4 proj_matrix;

out vec2 uv;

void main() {
	gl_Position = vec4(position, 0.0f, 1.0);
	//gl_Position = proj_matrix * vec4(view_matrix * model_matrix * vec3(position, 1.0f), 1.0f);

	uv = in_uv;
}