#include "Camera.hpp"
#include <glm/gtc/matrix_transform.hpp>

void mouse_callback(GLFWwindow* window, double xpos, double ypos){
    Camera* camera = static_cast<Camera*>(glfwGetWindowUserPointer(window));
    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) != GLFW_PRESS){
        camera->mousePressed = false;
        return;
    }
    if (!camera->mousePressed){
        camera->lastX = xpos;
        camera->lastY = ypos;
        camera->mousePressed = true;
        return;
    }
    float xoffset = xpos - camera->lastX;
    float yoffset = camera->lastY - ypos;
    camera->lastX = xpos;
    camera->lastY = ypos;
    float sensitivity = 0.1f;
    xoffset *= sensitivity;
    yoffset *= sensitivity;
    camera->yaw += xoffset;
    camera->pitch += yoffset;
    if (camera->pitch > 89.0f){
        camera->pitch = 89.0f;
    }
    if (camera->pitch < -89.0f){
        camera->pitch = -89.0f;
    }
    glm::vec3 direction;
    direction.x = cos(glm::radians(camera->yaw))*cos(glm::radians(camera->pitch));
    direction.y = sin(glm::radians(camera->pitch));
    direction.z = sin(glm::radians(camera->yaw)) * cos(glm::radians(camera->pitch));
    camera->front = glm::normalize(direction);
}