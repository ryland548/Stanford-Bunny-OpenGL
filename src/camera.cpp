#include "../inc/camera.hpp"
#include <iostream>

void Camera::init(int width, int height, glm::vec3 position) {
    Camera::width = width;
    Camera::height = height;
    pos = position;
}

void Camera::Matrix(Shader& shader) {
    glm::mat4 view = glm::mat4(1.0f);
    glm::mat4 projection = glm::mat4(1.0f);

    view = glm::lookAt(pos, pos + orientation, up);
    projection = glm::perspective(glm::radians(fovDeg), static_cast<float>(width) / static_cast<float>(height), nearPlane, farPlane);

    glm::mat4 camMatrix = projection * view;
    shader.setMat4("camMatrix", camMatrix);
}

void Camera::Inputs(GLFWwindow* window) {
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
        pos += speed * orientation;
    }
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
        pos += speed * -glm::normalize(glm::cross(orientation, up));
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
        pos += speed * -orientation;
    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
        pos += speed * glm::normalize(glm::cross(orientation, up));
    }
}
