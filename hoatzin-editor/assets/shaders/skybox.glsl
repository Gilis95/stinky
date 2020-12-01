#type vertex
#version 330 core

layout(location = 0) in vec4 position;

uniform mat4 u_ViewMatrix;
uniform mat4 u_ProjectionMatrix;
uniform mat4 u_ModelMatrix;

out vec4 v_TexCoord;

void main()
{
    gl_Position =  position;
    v_TexCoord = u_ViewMatrix * vec4(position.xyz, 0.0f);
}

#type fragment
#version 330 core

layout(location = 0) out vec4 color;

uniform samplerCube u_Texture;

in vec4 v_TexCoord;

void main()
{
    color = texture(u_Texture, v_TexCoord.xyz);
}