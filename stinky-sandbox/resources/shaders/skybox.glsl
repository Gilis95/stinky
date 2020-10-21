#type vertex
#version 330 core

layout(location = 0) in vec4 position;

uniform mat4 u_ViewProjection;
out vec4 v_TexCoord;

void main()
{
    vec4 pos = vec4(position.xy, -3.0, 1.0);
    gl_Position = pos;
    v_TexCoord = u_ViewProjection * pos;
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