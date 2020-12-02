#version 430 core
layout(location = 0) in vec3 in_pos;
layout(location = 1) in vec3 in_color;
out vec3 pass_color;
uniform mat4 model;
uniform mat4 projection;
void main() {
    gl_Position = projection * model * vec4(in_pos, 1);
    pass_color = in_color;
}