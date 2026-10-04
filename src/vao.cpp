#include "../inc/vao.hpp"

void VAO::init() {
    glGenVertexArrays(1, &ID);
}

VAO::~VAO() {
    destroy();
}

void VAO::bind() {
    glBindVertexArray(ID);
}

void VAO::unbind() {
    glBindVertexArray(0);
}

void VAO::destroy() {
    if (ID != 0) {
        glDeleteVertexArrays(1, &ID);
        ID = 0;
    }
}

void VAO::linkAttrib(GLuint location, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void* pointer) {
    glVertexAttribPointer(location, size, type, normalized, stride, pointer);
    glEnableVertexAttribArray(location);
}
