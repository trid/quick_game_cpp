#version 330 core

layout(location = 0) in vec3 in_vertexPosition;

void main() {
    gl_Position.xyz = in_vertexPosition * 0.1;
    //gl_Position.z -= 10;
    gl_Position.w = 1.0;
}