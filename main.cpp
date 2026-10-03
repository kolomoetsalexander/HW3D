#include <fstream>
#include <string>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Shaders.hpp"
#include "Camera.hpp"
#include "Geometry.hpp"
#include "Input.hpp"
#include <iostream>
#include "Intersection.hpp"
int main(){
    std::vector<Triangle> triangles = readTrianglesFromStdin();
    
    //когда то здесь будет реализация пересечений
    std::vector<bool> intersects(triangles.size(), false);
     for (size_t i = 0; i < triangles.size(); ++i){
        for (size_t j = i + 1; j < triangles.size(); ++j){
            if (trianglesIntersect(triangles[i], triangles[j])){
                intersects[i] = true;
                intersects[j] = true;
            }
        }
    }


     
    glfwInit();
    GLFWwindow* window = glfwCreateWindow(3200, 2000, "HW3D", nullptr, nullptr);
    glfwMakeContextCurrent(window);
    // инициализируем GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        glfwTerminate();
        return -1;
    }
    //глубина цвета
    glEnable(GL_DEPTH_TEST);

    Geometry scene = createScene(triangles, intersects);
    GLuint shaderProgram = createShaderProgram("shaders/vertex.glsl", "shaders/fragment.glsl");
    glm::mat4 model = glm::mat4(1.0f);
    GLuint modelLoc = glGetUniformLocation(shaderProgram, "model");

    glm::mat4 view = glm::mat4(1.0f);
    GLuint viewLoc = glGetUniformLocation(shaderProgram, "view");

    glm::mat4 perspective = glm::mat4(1.0f);
    perspective = glm::perspective(glm::radians(70.0f), 3200.0f / 2000.0f, 0.1f, 200.0f);
    GLuint perspectiveLoc = glGetUniformLocation(shaderProgram, "perspective");

    GLuint lightPosLoc = glGetUniformLocation(shaderProgram, "lightPos");
    GLuint viewPosLoc = glGetUniformLocation(shaderProgram, "viewPos");
    glm::vec3 lightPos(5.0f, 8.0f, 5.0f);

    Camera camera;
    camera.position = glm::vec3(0.0f, 0.0f, 3.0f);
    camera.front = glm::vec3(0.0f, 0.0f, -1.0f);
    camera.up = glm::vec3(0.0f, 1.0f, 0.0f);
    camera.yaw = -90.0f;
    camera.pitch = 0.0f;
    camera.lastX = 1600.0f;
    camera.lastY = 1000.0f;
    camera.mousePressed = false;

    glfwSetWindowUserPointer(window, &camera);
    glfwSetCursorPosCallback(window, mouse_callback);
    glClearColor(0.1f, 0.2f, 0.3f, 1.0f);

    float speed = 0.05f;
    while(!glfwWindowShouldClose(window)){
        if(glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS){
            camera.position += camera.front*speed;
        }
        if(glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS){
            camera.position -= camera.front*speed;
        }
        glm::vec3 cameraRight = glm::normalize(glm::cross(camera.front, camera.up));
        if(glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS){
            camera.position += cameraRight*speed;
        }
        if(glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS){
            camera.position -= cameraRight*speed;
        }

        view = glm::lookAt(camera.position, camera.position + camera.front, camera.up);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glfwPollEvents();

        glUseProgram(shaderProgram);
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
        glUniformMatrix4fv(perspectiveLoc, 1, GL_FALSE, glm::value_ptr(perspective));
        glUniform3fv(lightPosLoc, 1, glm::value_ptr(lightPos));
        glUniform3fv(viewPosLoc, 1, glm::value_ptr(camera.position));

        glBindVertexArray(scene.VAO);
        glDrawArrays(GL_TRIANGLES, 0, scene.vertexCount);

        glfwSwapBuffers(window);
    }
    glfwTerminate();
    return 0;
}