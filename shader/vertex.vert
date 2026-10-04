#version 410 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoord;

out vec3 Normal;

uniform mat4 camMatrix;
uniform mat4 modelMatrix;

void main() {
    gl_Position = camMatrix * modelMatrix * vec4(aPos, 1.0);

    Normal = mat3(transpose(inverse(modelMatrix))) * aNormal;
}
