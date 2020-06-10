#version 330 core
layout (location = 0) in vec3 aPos;
out vec4 vertexColor;

void main() {
    gl_Position = vec4(aPos, 1.0);
    vertexColor = vec4(aPos.x / 2 + 0.5, aPos.y / 2 + 0.5, aPos.z / 2 + 0.5, 1);
}
