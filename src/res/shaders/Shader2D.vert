#version 460 core

layout (location = 0) in vec2 a_Position;
layout (location = 1) in vec2 a_TexCoord;

uniform mat4 u_TransformationMatrix;
uniform mat4 u_ProjectionMatrix;
uniform mat4 u_ViewMatrix;

out vec2 v_TexCoord;

void main()
{
    v_TexCoord = a_TexCoord;
    vec4 worldPosition = u_TransformationMatrix * vec4(a_Position, 0.0, 1.0);
    gl_Position = u_ProjectionMatrix * u_ViewMatrix * worldPosition; //MVP model, view projection. In matrix multiplication, it is done as projection, view, model
}