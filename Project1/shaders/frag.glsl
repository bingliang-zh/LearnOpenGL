#version 330 core
out vec4 FragColor;

in vec2 texCoord;
in vec3 vertColor;

uniform sampler2D texture0;
uniform sampler2D texture1;

void main() {
//    FragColor = vec4(vertColor, 1.0);
//	FragColor = texture(texture0, texCoord);
	FragColor = mix(texture(texture0, texCoord), texture(texture1, texCoord), 0.5);
}
