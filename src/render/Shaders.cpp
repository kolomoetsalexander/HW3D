#include "render/Shaders.hpp"
#include <fstream>
#include <string>

//read shaders from the files
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
    glShaderSource(shader, 1, &sourceCStr, nullptr);
    glCompileShader(shader);
    return shader;
}
GLuint createShaderProgram(const char* vertexFilename, const char* fragmentFilename){
    GLuint vertexShader = compileShader(GL_VERTEX_SHADER, vertexFilename);
    GLuint fragmentShader = compileShader(GL_FRAGMENT_SHADER, fragmentFilename);
    //create shader program
    GLuint shaderProgram = glCreateProgram();

    //add shaders to rhe program
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    return shaderProgram;
}