#version 330 core

layout(location = 0) in vec3 in_vertexPosition;

uniform mat4 u_rotation;
uniform mat4 u_view;
uniform mat4 u_translation;
uniform mat4 u_camera;

void main() {
    vec4 vertexPosition = vec4(in_vertexPosition, 1.0);

    gl_Position = u_camera * vertexPosition;
}