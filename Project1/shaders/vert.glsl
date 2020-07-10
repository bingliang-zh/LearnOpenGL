#version 330 core
layout (location = 0) in vec3 pos;
layout (location = 1) in vec3 color;
layout (location = 2) in vec2 iTexCoord;
layout (location = 3) in vec2 iTexCoord2;

out vec2 texCoord;
out vec2 texCoord2;
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main() {
    gl_Position = projection * view * model * vec4(pos, 1.0);
    texCoord = iTexCoord;
    texCoord2 = iTexCoord2;
}
