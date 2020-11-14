#type vertex
#version 330 core
layout(location = 0) in vec3 position;
//layout(location = 1) in vec2 texCoord;

uniform mat4 u_ViewMatrix;
uniform mat4 u_ProjectionMatrix;
uniform mat4 u_ModelMatrix;
//out vec2 v_TexCoord;

void main() {
    gl_Position = u_ProjectionMatrix * u_ViewMatrix * u_ModelMatrix * vec4(position, 1.0) ;
//    v_TexCoord = texCoord;
}

#type fragment
#version 330 core

layout(location = 0) out vec4 color;

//in vec2 v_TexCoord;

uniform sampler2D u_Texture;

void main() {
//    vec4 texColor = texture(u_Texture, v_TexCoord);
    color = vec4(1.0, 0.0 , 0.0, 1.0);
}