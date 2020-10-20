#version 400 core

layout (location = 0) in vec2 a_position; // The vertex coordinates
layout (location = 1) in vec3 a_color; // The vertex color

out vec3 v_color; // The color that is passed to the fragment shader and interpolated

void main() {
    v_color = a_color; // Pass the vertex color to the fragment shader
    gl_Position = vec4(a_position, 0.0, 1.0); // Set the vertex position in the clip space
}
