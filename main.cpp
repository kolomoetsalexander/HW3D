#include <fstream>
#include <string>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Shaders.hpp"
#include "Camera.hpp"
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

    float vertices[] =
    {
        0.0f,  0.6f,  0.0f,//0-верхняя
        -0.6f, -0.4f,  0.4f,//1-левая
        0.6f, -0.4f,  0.4f, //2-правая
        0.0f, -0.4f, -0.6f//3-задняя
    };
    unsigned int indices[] = 
    {
        0, 1, 2,
        0, 3, 1,
        0, 2, 3,
        1, 3, 2
    };
    GLuint VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);
    GLuint VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    // загружаем в буффер
    glBufferData(
        GL_ARRAY_BUFFER,
        sizeof(vertices),
        vertices,
        GL_STATIC_DRAW
    );
    GLuint EBO;
    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(
        GL_ELEMENT_ARRAY_BUFFER,
        sizeof(indices),
        indices,
        GL_STATIC_DRAW
    );
    // говорим, как читать то, что загрузили
    glVertexAttribPointer(
        0,
        3,
        GL_FLOAT,
        GL_FALSE,
        3 * sizeof(float),
        (void*)0
    );
    glEnableVertexAttribArray(0);

    GLuint vertexShader = compileShader(GL_VERTEX_SHADER, "shaders/vertex.glsl");
    GLuint fragmentShader = compileShader(GL_FRAGMENT_SHADER, "shaders/fragment.glsl");
    // Создаём shader program
    GLuint shaderProgram = glCreateProgram();

    // Добавляем шейдеры в программу
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    int success;
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);

    if (!success) {
        char infoLog[512];
        glGetProgramInfoLog(shaderProgram, 512, nullptr, infoLog);
        std::cout << infoLog << std::endl;
    }
    //создаем матрицу поворота
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::rotate(model, glm::radians(45.0f), glm::vec3(0.0f, 1.0f, 0.0f));
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
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
        glUniformMatrix4fv(perspectiveLoc, 1, GL_FALSE, glm::value_ptr(perspective));
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 12, GL_UNSIGNED_INT, 0);
        glfwSwapBuffers(window);
    }
    glfwTerminate();
    return 0;
}