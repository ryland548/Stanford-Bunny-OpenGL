#include "../inc/app.hpp"
#include <iostream>
#include <glad/glad.h>
#include <glm/gtc/matrix_transform.hpp>

void framebufferSizeCallback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

bool App::init() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_DECORATED, GLFW_FALSE);
    #ifdef __APPLE__
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    #endif
    if (!window.init()) {
        destroy();
        return false;
    }
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to init GLAD.\n";
        return false;
    }
    glfwSwapInterval(1);
    int width, height;
    glfwGetFramebufferSize(window.getWindow(), &width, &height);
    glViewport(0, 0, width, height);
    glEnable(GL_DEPTH_TEST);
    glfwSetFramebufferSizeCallback(window.getWindow(), framebufferSizeCallback);
    vao.init();
    vbo.init();
    ebo.init();
    shader.init("./shader/vertex.vert", "./shader/fragment.frag");
    meshData = loader.loadOBJ("./mesh/bunny.obj");
    camera.init(window.getWidth(), window.getHeight(), glm::vec3(0.0, 0.1, 0.30));
    vao.bind();
    vbo.bind();
    vbo.upload(meshData.vertices);
    ebo.bind();
    ebo.upload(meshData.indices);
    vao.linkAttrib(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
    vao.linkAttrib(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));
    vao.linkAttrib(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, texCoords));
    return true;
}

void App::input() {
    if (glfwGetKey(window.getWindow(), GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window.getWindow(), true);
    }
    static bool mKeyWasPressed = false;
    bool mKeyIsPressed = (glfwGetKey(window.getWindow(), GLFW_KEY_M) == GLFW_PRESS);

    if (mKeyIsPressed && !mKeyWasPressed) {
        if (!wireframe) {
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
            wireframe = true;
        } else {
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
            wireframe = false;
        }
    }

    mKeyWasPressed = mKeyIsPressed;

    camera.Inputs(window.getWindow());
    camera.Inputs(window.getWindow());
}

void App::calculateModel() {
    model = glm::mat4(1.0f);
    double currentSystemTime = glfwGetTime();
    float cleanTime = static_cast<float>(std::fmod(currentSystemTime, 8.0));
    float rotationSpeed = glm::radians(45.0f);
    float currentAngle = cleanTime * rotationSpeed;
    model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
    model = glm::rotate(model, currentAngle, glm::vec3(0.0f, 1.0f, 0.0f));
    model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));

    shader.setMat4("modelMatrix", model);
}

void App::loop() {
    while (!glfwWindowShouldClose(window.getWindow())) {
        float currentFrame = static_cast<float>(glfwGetTime());
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;
        input();
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        shader.bind();
        calculateModel();
        camera.Matrix(shader);
        vao.bind();
        glDrawElements(GL_TRIANGLES, meshData.indices.size(), GL_UNSIGNED_INT, 0);
        glfwSwapBuffers(window.getWindow());
        glfwPollEvents();
    }
}

bool App::run() {
    if (!init()) {
        std::cout << "Error init.\n";
        return false;
    }
    loop();
    destroy();
    return true;
}

void App::destroy() {
    window.destroy();
    glfwTerminate();
}
