#include "../inc/vbo.hpp"

void VBO::init() {
    glGenBuffers(1, &ID);
}

VBO::~VBO() {
    destroy();
}

void VBO::bind() {
    glBindBuffer(GL_ARRAY_BUFFER, ID);
}

void VBO::unbind() {
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VBO::upload(const std::vector<Vertex>& vertices) {
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), vertices.data(), GL_STATIC_DRAW);
}

void VBO::destroy() {
    if (ID != 0) {
        glDeleteBuffers(1, &ID);
        ID = 0;
    }
}
