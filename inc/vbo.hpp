#pragma once
#include <glad/glad.h>
#include "vertex.hpp"

class VBO {
public:
    ~VBO();
    void init();
    void bind();
    void unbind();
    void upload(const std::vector<Vertex>& vertices);
    void destroy();
private:
    GLuint ID;
};
