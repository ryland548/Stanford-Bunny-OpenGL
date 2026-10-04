#include "../inc/shader.hpp"
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <fstream>

std::string readFile(std::string filePath) {
    std::ifstream file(filePath);

    if (!file.is_open()) {
        std::cout << "Error opening file. File Path: " << filePath << '\n';
        return "";
    }
    std::string content;
    std::string line;
    while (std::getline(file, line)) {
        content += line + '\n';
    }

    file.close();
    return content;
}

void Shader::init(const std::string& vertexPath, const std::string& fragmentPath) {
    std::string vertexShaderString = readFile(vertexPath);
    std::string fragmentShaderString = readFile(fragmentPath);

    const char* vertexShaderSource = vertexShaderString.c_str();
    const char* fragmentShaderSource = fragmentShaderString.c_str();

    GLuint vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
    glCompileShader(vertexShader);

    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "Vertex Shader Compilation Failed.\n" << infoLog << '\n';
    }

    GLuint fragmentShader;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, nullptr);
    glCompileShader(fragmentShader);

    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(fragmentShader, 512, nullptr, infoLog);
        std::cout << "Fragment Shader Compilation Failed.\n" << infoLog << '\n';
    }

    ID = glCreateProgram();
    glAttachShader(ID, vertexShader);
    glAttachShader(ID, fragmentShader);
    glLinkProgram(ID);

    glGetProgramiv(ID, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(ID, 512, nullptr, infoLog);
        std::cout << "Shader Program Linking Failed.\n" << infoLog << '\n';
    }

    glUseProgram(ID);
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

Shader::~Shader() {
    destroy();
}

void Shader::setMat4(const std::string& name, const glm::mat4& value) {
    GLint location = glGetUniformLocation(ID, name.c_str());
    if (location == -1) {
        std::cout << "Error finding location. :" << location << '\n';
    }
    glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(value));
}

void Shader::bind() {
    glUseProgram(ID);
}

void Shader::unbind() {
    glUseProgram(0);
}

void Shader::destroy() {
    if (ID != 0) {
        glDeleteProgram(ID);
        ID = 0;
    }
}
