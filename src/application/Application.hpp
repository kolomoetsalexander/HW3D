#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include "render/Camera.hpp"
#include "geometry/Triangle.hpp"
#include "render/Camera.hpp"
#include "render/Mesh.hpp"
#include "render/Renderer.hpp"
#include <vector>

class Application{
public:
    Application();
    ~Application();
    Application(const Application&) = delete;
    Application& operator=(const Application&) = delete;
    void run(const std::vector<Triangle>& triangles, const std::vector<bool>& intersects);
private:
    bool initialize();
    void processInput(Camera& camera);
    GLFWwindow* window = nullptr;
    bool glfwInitialized = false;
};