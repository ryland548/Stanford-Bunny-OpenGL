#pragma once
#include <glad/glad.h>
#include <vector>

class EBO {
public:
    ~EBO();
    void init();
    void bind();
    void unbind();
    void upload(const std::vector<GLuint>& indices);
    void destroy();
private:
    GLuint ID;
};
