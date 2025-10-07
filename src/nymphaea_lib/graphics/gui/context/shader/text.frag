#version 460 core

in vec2 uv;

uniform sampler2D glyph;

out vec4 color;

void main() {

    vec4 fragment = vec4(1.0, 1.0, 1.0, texture(glyph, uv).r);
    if (fragment.a < 0.1) {
        discard;
    }
    //color = vec4(1.0, 1.0, 1.0, 1.0);
    color = fragment;
}