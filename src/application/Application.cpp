#include "Application.hpp"

Application::Application() = default;
Application::~Application(){
    if(window != nullptr)
        glfwDestroyWindow(window);
    if(glfwInitialized)
        glfwTerminate();
}
bool Application::initialize(){
    if(glfwInit())
        glfwInitialized = true;
    else
        return false;
    window = glfwCreateWindow(3200, 2000, "HW3D", nullptr, nullptr);
    if (window == nullptr)
        return false;
    glfwMakeContextCurrent(window);
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
        return false;
    }
    glEnable(GL_DEPTH_TEST);
    return true;
}
void Application::processInput(Camera& camera){
    float speed = 0.05f;

    if(glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS){
        camera.processKeyboard(camera.getFront() * speed);
    }
    if(glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS){
        camera.processKeyboard(-camera.getFront() * speed);
    }
    if(glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS){
        camera.processKeyboard(camera.getRight() * speed);
    }
    if(glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS){
        camera.processKeyboard(-camera.getRight() * speed);
    }
}
void Application::run(const std::vector<Triangle>& triangles, const std::vector<bool>& intersects){
    if (!initialize())
        return;
    Mesh mesh (triangles, intersects);
    ShaderProgram shader("shaders/vertex.glsl", "shaders/fragment.glsl");
    Renderer renderer(mesh, shader);
    Camera camera;
    glfwSetWindowUserPointer(window, &camera);
    glfwSetCursorPosCallback(window, mouse_callback);
    glClearColor(0.1f, 0.2f, 0.3f, 1.0f);
    while (!glfwWindowShouldClose(window)){
        processInput(camera);
        glfwPollEvents();
        renderer.render(camera);
        glfwSwapBuffers(window);
    }
}
