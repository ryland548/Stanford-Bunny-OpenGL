#include "../inc/window.hpp"

bool Window::init() {
    window = glfwCreateWindow(width, height, name.c_str(), nullptr, nullptr);
    if (!window) {
        destroy();
        return false;
    }
    glfwMakeContextCurrent(window);
    return true;
}

void Window::destroy() {
    if (window) {
        glfwDestroyWindow(window);
    }
}

GLFWwindow* Window::getWindow() {
    return window;
}

int Window::getWidth() {
    return width;
}

int Window::getHeight() {
    return height;
}

