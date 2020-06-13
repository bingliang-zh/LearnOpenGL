#version 330 core
layout (location = 0) in vec3 pos;
layout (location = 1) in vec3 color;

out vec3 vertColor;
//uniform vec2 screenSpaceOffset;

void main() {
    // practice 1: 上下颠倒
    // gl_Position = vec4(pos.x, -pos.y, pos.z, 1.0);
    // practice 2: 屏幕空间位移
    // gl_Position = vec4(pos.x + screenSpaceOffset.x, pos.y + screenSpaceOffset.y, pos.z, 1.0);
    gl_Position = vec4(pos, 1.0);
    // practice 3
    // 左下角黑色原因因为传过去的是负数，被夹了。
    vertColor = pos;
}
