#pragma once
#include "loader.hpp"
#include "window.hpp"
#include "shader.hpp"
#include "vao.hpp"
#include "ebo.hpp"
#include "vertex.hpp"
#include "vbo.hpp"
#include "camera.hpp"

class App {
public:
    ~App() = default;
    bool run();
    bool init();
    void input();
    void loop();
    void calculateModel();
    void destroy();
private:
    Window window;
    Loader loader;
    MeshData meshData;
    VAO vao;
    VBO vbo;
    EBO ebo;
    Shader shader;
    Camera camera;
    glm::mat4 model = glm::mat4(1.0f);
    float timeValue = 1.5f;
    float deltaTime = 0.0f;
    float lastFrame = 0.0f;
    bool wireframe = false;
};
