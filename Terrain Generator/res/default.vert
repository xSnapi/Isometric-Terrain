varying vec2 i_tex;
varying vec4 i_color;

void main() {
	i_tex		= gl_TextureMatrix[0] * gl_MultiTexCoord0;
	gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;
	i_color 	= gl_Color;
}