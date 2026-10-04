#pragma once
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtx/vector_angle.hpp>
#include "shader.hpp"
#include <GLFW/glfw3.h>

class Camera {
public:
    glm::vec3 pos;
    glm::vec3 orientation = glm::vec3(0.0f, 0.0f, -1.0f);
    glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);

    int width;
    int height;

    float speed = 0.01f;

    float fovDeg = 45.0f;
    float nearPlane = 0.01f;
    float farPlane = 10000.0f;

    void init(int width, int height, glm::vec3 position);
    ~Camera() = default;

    void Matrix(Shader& shader);
    void Inputs(GLFWwindow* window);
private:

};
