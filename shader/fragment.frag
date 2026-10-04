#version 410 core

out vec4 FragColor;

in vec3 Normal;

void main() {
    vec3 norm = normalize(Normal);
    vec3 normalColor = norm * 0.5 + 0.5;
    FragColor = vec4(normalColor, 1.0);
}
