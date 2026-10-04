#pragma once
#include <glad/glad.h>

class VAO {
public:
    ~VAO();
    void init();
    void bind();
    void unbind();
    void destroy();
    void linkAttrib(GLuint location, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void* pointer);
private:
    GLuint ID;
};
