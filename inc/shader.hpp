#pragma once
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <string>

std::string readFile(std::string filePath);

class Shader {
public:
    void init(const std::string& vertexPath, const std::string& fragmentPath);
    ~Shader();
    void bind();
    void unbind();
    void destroy();
    void setMat4(const std::string& name, const glm::mat4& value);
private:
    GLuint ID;
};
