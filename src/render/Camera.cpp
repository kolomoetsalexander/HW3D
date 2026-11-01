#include "render/Camera.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <cmath>
Camera::Camera():
    position(0.0f, 0.0f, 3.0f),
    front(0.0f, 0.0f, -1.0f),
    up(0.0f, 1.0f, 0.0f),
    yaw(-90.0f),
    pitch(0.0f),
    lastX(0.0f),
    lastY(0.0f),
    mousePressed(false){}
glm::mat4 Camera::getViewMatrix() const{
    return glm::lookAt(position, position + front, up);
}
void Camera::processKeyboard(const glm::vec3& movement){
    position += movement;
}

void Camera::processMouseMovement(double xpos, double ypos, bool buttonPressed){
    if(!buttonPressed){
        mousePressed = false;
        return;
    }
    if (!mousePressed){
        lastX = xpos;
        lastY = ypos;
        mousePressed = true;
        return;
    }
    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos;
    lastX = xpos;
    lastY = ypos;
    float sensitivity = 0.1f;
    xoffset *= sensitivity;
    yoffset *= sensitivity;
    yaw += xoffset;
    pitch += yoffset;
    if (pitch > 89.0f){
        pitch = 89.0f;
    }
    if (pitch < -89.0f){
        pitch = -89.0f;
    }
    updateCameraVectors();
}
void Camera::updateCameraVectors(){
    glm::vec3 direction;
    direction.x = cos(glm::radians(yaw))*cos(glm::radians(pitch));
    direction.y = sin(glm::radians(pitch));
    direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    front = glm::normalize(direction);
}
void mouse_callback(GLFWwindow* window, double xpos, double ypos){
    Camera* camera = static_cast<Camera*>(glfwGetWindowUserPointer(window));

    if (camera == nullptr){
        return;
    }
    bool buttonPressed = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS;
    camera->processMouseMovement(xpos, ypos, buttonPressed);
}
glm::vec3 Camera::getPosition() const{
    return position;
}
glm::vec3 Camera::getFront() const{
    return front;
}
glm::vec3 Camera::getRight() const{
    return glm::normalize(glm::cross(front, up));
}