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
#include <iostream>
int main(){
    glfwInit();
    GLFWwindow* window = glfwCreateWindow(
        3200,
        2000,
        "HW3D",
        nullptr,
        nullptr
    );
    glfwMakeContextCurrent(window);
    // инициализируем GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        glfwTerminate();
        return -1;
    }
    //глубина цвета
    glEnable(GL_DEPTH_TEST);
    glm::vec3 A(0.0f, 0.6f, 0.0f);
    glm::vec3 B(-0.6f, -0.4f, 0.4f);
    glm::vec3 C(0.6f, -0.4f, 0.4f);
    Geometry figure = createTriangule(A, B, C);

    glm::vec3 D(0.0f, 0.6f, -0.5f);
    glm::vec3 E(-0.6f, -0.4f, -0.5f);
    glm::vec3 F(0.6f, -0.4f, -0.5f);
    Geometry figure2 = createTriangule(D, E, F);

    GLuint shaderProgram = createShaderProgram("shaders/vertex.glsl", "shaders/fragment.glsl");
    //создаем матрицу поворота
    glm::mat4 model1 = glm::mat4(1.0f);
    model1 = glm::rotate(model1, glm::radians(45.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    glm::mat4 model2 = glm::mat4(1.0f);
    model2 = glm::translate(model2, glm::vec3(0.0f, 0.0f, -1.0f));
    GLuint modelLoc = glGetUniformLocation(shaderProgram, "model");

     //матрица камеры
    glm::mat4 view = glm::mat4(1.0f);
    GLuint viewLoc = glGetUniformLocation(shaderProgram, "view");
    
    //матрица перспективы
    glm::mat4 perspective = glm::mat4(1.0f);
    perspective = glm::perspective(glm::radians(90.0f), 3200.0f / 2000.0f, 0.1f, 100.0f);
    GLuint perspectiveLoc = glGetUniformLocation(shaderProgram, "perspective");

    Camera camera;
    camera.position = glm::vec3(1.0f, 0.0f, 3.0f);
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

    //скорость перемещения
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
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model1));
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model2));
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
        glUniformMatrix4fv(perspectiveLoc, 1, GL_FALSE, glm::value_ptr(perspective));
        glBindVertexArray(figure.VAO);
        glDrawElements(GL_TRIANGLES, figure.indexCount, GL_UNSIGNED_INT, 0);
        glBindVertexArray(figure2.VAO);
        glDrawElements(GL_TRIANGLES, figure2.indexCount, GL_UNSIGNED_INT, 0);
        glfwSwapBuffers(window);
    }
    glfwTerminate();
    return 0;
}