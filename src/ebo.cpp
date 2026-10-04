#include "../inc/ebo.hpp"

void EBO::init() {
    glGenBuffers(1, &ID);
}

EBO::~EBO() {
    destroy();
}

void EBO::bind() {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
}

void EBO::unbind() {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void EBO::upload(const std::vector<GLuint>& indices) {
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), indices.data(), GL_STATIC_DRAW);
}

void EBO::destroy() {
    if (ID != 0) {
        glDeleteBuffers(1, &ID);
        ID = 0;
    }
}
