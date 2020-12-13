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

// uniform sampler2D u_Texture;

void main() {
//    vec4 texColor = texture(u_Texture, v_TexCoord);

    vec2 st = gl_FragCoord.xy/vec2(1280,780);

    vec3 color1 = vec3(1.9,0.55,0);
    vec3 color2 = vec3(0.226,0.000,0.615);

    float mixValue = distance(st,vec2(0,1));
    color = vec4(mix(color1,color2,mixValue),1.0);
}