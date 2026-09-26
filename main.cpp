#include <fstream>
#include <string>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
std::string readFile(const char* filename){
    std::ifstream file(filename);
    std::string line;
    std::string source;
    while(std::getline(file, line)){
        source += line;
        source += "\n";
    }
    return source;
}
GLuint compileShader(GLuint type, const char* filename){
    std::string source = readFile(filename);
    const char* sourceCStr = source.c_str();
    GLuint shader = glCreateShader(type);
    glShaderSource(
        shader,
        1,
        &sourceCStr,
        nullptr
    );
    glCompileShader(shader);
    return shader;
}
int main(){
    glfwInit();
    GLFWwindow* window = glfwCreateWindow(
        800,
        600,
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
    float vertices[] =
    {
         0.0f,  0.5f, 0.0f,
        -0.5f, -0.5f, 0.0f,
         0.5f, -0.5f, 0.0f
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
    // говорим, как читать то, что загрузили
    glVertexAttribPointer(
        0,
        3,
        GL_FLOAT,
        GL_FALSE,
        3 * sizeof(float),
        (void*)0
    );
    // создаем шейдеры
    glEnableVertexAttribArray(0);
    GLuint vertexShader = compileShader(
        GL_VERTEX_SHADER,
        "shaders/vertex.glsl"
    );
    GLuint fragmentShader = compileShader(
        GL_FRAGMENT_SHADER,
        "shaders/fragment.glsl"
    );
    // Создаём shader program
    GLuint shaderProgram = glCreateProgram();
    // Добавляем шейдеры в программу
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    glClearColor(0.1f, 0.2f, 0.3f, 1.0f);
    while(!glfwWindowShouldClose(window)){
        glClear(GL_COLOR_BUFFER_BIT);
        glfwPollEvents();
        glUseProgram(shaderProgram);
        glBindVertexArray(VAO);
        glDrawArrays(
            GL_TRIANGLES, 0, 3);
        glfwSwapBuffers(window);
    }
    glfwTerminate();
    return 0;
}