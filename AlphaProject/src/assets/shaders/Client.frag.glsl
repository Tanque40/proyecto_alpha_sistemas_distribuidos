#version 410 core

layout (location = 0) out vec4 o_Color;

in vec4 v_Color;
in vec2 v_TexCoord;
in float v_TexIndex;

uniform sampler2D u_Textures[16];

void main(){
	int index = int(v_TexIndex);
	o_Color = texture(u_Textures[0], v_TexCoord) * v_Color;
}