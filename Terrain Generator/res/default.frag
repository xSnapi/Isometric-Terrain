#version 330

precision lowp float;

layout(location = 0) out vec4 o_color;

in vec2 i_tex;
in vec4 i_color;

uniform sampler2D texture;

void main() {
	vec4 pixel = texture2D(texture, i_tex);
	o_color = pixel * vec4(1.0, 0.0, 0.0, 1.0);
}