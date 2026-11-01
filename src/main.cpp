#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "render/Camera.hpp"
#include "render/Mesh.hpp"
#include "render/Renderer.hpp"
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
    Renderer renderer(mesh, shader);

    Camera camera;
    

    glfwSetWindowUserPointer(window, &camera);
    glfwSetCursorPosCallback(window, mouse_callback);
    glClearColor(0.1f, 0.2f, 0.3f, 1.0f);

    float speed = 0.05f;
    while(!glfwWindowShouldClose(window)){
        if(glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS){
            camera.processKeyboard(camera.getFront()*speed);
        }
        if(glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS){
            camera.processKeyboard(-camera.getFront()*speed);
        }
        if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
            camera.processKeyboard(camera.getRight() * speed);
        }
        if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
            camera.processKeyboard(-camera.getRight() * speed);
        }
        glfwPollEvents();
        renderer.render(camera);

        glfwSwapBuffers(window);
    }
    glfwTerminate();
    return 0;
}