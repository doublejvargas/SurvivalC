#version 460 core

in vec2 v_TexCoord;
in float v_TexIndex;

layout(location = 0) out vec4 o_Color;

uniform sampler2D u_Textures[3];

void main()
{    
    int index = int(v_TexIndex);
    o_Color = texture(u_Textures[index], v_TexCoord);
}