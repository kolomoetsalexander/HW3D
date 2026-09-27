#pragma once
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <GLFW/glfw3.h>

struct Camera{
    glm::vec3 position;
    glm::vec3 front;
    glm::vec3 up;
    float yaw;
    float pitch;
    float lastX;
    float lastY;
    bool mousePressed;
};
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
