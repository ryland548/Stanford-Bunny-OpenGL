#pragma once
#include <GLFW/glfw3.h>
#include <string>

class Window {
public:
    ~Window() = default;
    bool init();
    void destroy();
    GLFWwindow* getWindow();
    int getWidth();
    int getHeight();
private:
    GLFWwindow* window = nullptr;
    int width = 800;
    int height = 800;
    std::string name = "Stanford Bunny";
};
