#include <fstream>
#include <string>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "render/ShaderProgram.hpp"
#include "render/Camera.hpp"
#include "render/Mesh.hpp"
//#include "Input.hpp"
#include <iostream>
#include "geometry/Intersection.hpp"
#include "geometry/Grid.hpp"
#include "geometry/Test.hpp"
#include "geometry/Triangle.hpp"
int main(){
    long long n = 0;
    std::cin >> n;
    std::vector<Triangle> triangles = generateTriangles(n);

    //intersections
    std::vector<bool> intersects(triangles.size(), false);
    Grid grid(triangles);
    for (const auto& pair : grid.candidatePairs()){
        size_t i = pair.first;
        size_t j = pair.second;
        if (trianglesIntersect(triangles[i], triangles[j])){
            intersects[i] = true;
            intersects[j] = true;
        }
    }


     
    glfwInit();
    GLFWwindow* window = glfwCreateWindow(3200, 2000, "HW3D", nullptr, nullptr);
    glfwMakeContextCurrent(window);
    // initialize GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        glfwTerminate();
        return -1;
    }
    //colour deep
    glEnable(GL_DEPTH_TEST);

    Mesh mesh (triangles, intersects);
    ShaderProgram shader("shaders/vertex.glsl", "shaders/fragment.glsl");

    glm::mat4 model = glm::mat4(1.0f);
    GLint modelLoc = shader.getUniformLocation("model");

    glm::mat4 view = glm::mat4(1.0f);
    GLint viewLoc = shader.getUniformLocation("view");

    glm::mat4 perspective = glm::mat4(1.0f);
    perspective = glm::perspective(glm::radians(70.0f), 3200.0f / 2000.0f, 0.1f, 200.0f);
    GLint perspectiveLoc = shader.getUniformLocation("perspective");

    GLint lightPosLoc = shader.getUniformLocation("lightPos");
    GLint viewPosLoc = shader.getUniformLocation("viewPos");
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

        shader.use();
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
        glUniformMatrix4fv(perspectiveLoc, 1, GL_FALSE, glm::value_ptr(perspective));
        glUniform3fv(lightPosLoc, 1, glm::value_ptr(lightPos));
        glUniform3fv(viewPosLoc, 1, glm::value_ptr(camera.position));

        mesh.draw();

        glfwSwapBuffers(window);
    }
    glfwTerminate();
    return 0;
}