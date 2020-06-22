#version 330 core
layout (location = 0) in vec3 pos;
layout (location = 1) in vec3 color;
layout (location = 2) in vec2 iTexCoord;

out vec3 vertColor;
out vec2 texCoord;
//uniform vec2 screenSpaceOffset;

void main() {
    // practice 1: ���µߵ�
    // gl_Position = vec4(pos.x, -pos.y, pos.z, 1.0);
    // practice 2: ��Ļ�ռ�λ��
    // gl_Position = vec4(pos.x + screenSpaceOffset.x, pos.y + screenSpaceOffset.y, pos.z, 1.0);
    gl_Position = vec4(pos, 1.0);
    // practice 3
    // ���½Ǻ�ɫԭ����Ϊ����ȥ���Ǹ����������ˡ�
    vertColor = pos;
    texCoord = iTexCoord;
}
