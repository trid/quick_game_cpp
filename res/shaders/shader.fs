#version 330 core

out vec4 color;

uniform sampler2D uTextureSampler;


void main() {
    //color = texture(uTextureSampler, uvPosition).rgb;
    color = vec4(1.0, 0.0, 0.0, 1.0);
}