#pragma once
#include <glm/glm.hpp>
#include <GLFW/glfw3.h>

class Camera{
public:
    Camera();
    glm::mat4 getViewMatrix() const;
    void processMouseMovement(double xpos, double ypos, bool buttonPressed);
    void processKeyboard(const glm::vec3& movement);

    glm::vec3 getPosition() const;
    glm::vec3 getFront() const;
    glm::vec3 getRight() const;
private:
    glm::vec3 position;
    glm::vec3 front;
    glm::vec3 up;
    float yaw;
    float pitch;
    float lastX;
    float lastY;
    bool mousePressed;
    void updateCameraVectors();    
};
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
