#version 330 core

out vec3 color;

uniform sampler2D uTextureSampler;


void main() {
    //color = texture(uTextureSampler, uvPosition).rgb;
    color = vec3(uvPosition.x, uvPosition.y, 0.0);
}