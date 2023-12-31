#version 460 core

in vec2 v_TexCoord;

layout(location = 0) out vec4 o_Color;

uniform sampler2D u_Texture;

void main()
{    
    o_Color = texture(u_Texture, v_TexCoord);
}