#version 460 core

in vec2 UV;

out vec4 outColor;

uniform sampler2D tex;

void main() {
	//outColor = texture(tex, UV);

	outColor = vec4(texture(tex, UV).rgb, 1.0f);
	
	//outColor = vec4(1.0f, 0.0f, 0.0f, 1.0f);
}