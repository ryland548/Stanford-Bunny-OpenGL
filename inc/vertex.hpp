#pragma once
#include <glad/glad.h>
#include <vector>
#include <glm/glm.hpp>

struct Vertex {
    glm::vec3 pos;
    glm::vec3 normal;
    glm::vec2 texCoords;
};

struct MeshData {
    std::vector<Vertex> vertices;
    std::vector<GLuint> indices;
};
