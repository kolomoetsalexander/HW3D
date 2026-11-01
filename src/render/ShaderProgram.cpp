#include "render/ShaderProgram.hpp"
#include <fstream>
#include <iostream>
#include <string>

std::string readFile(const char* filename){
    std::ifstream file(filename);
    std::string source;
    std::string line;

    while (std::getline(file, line)){
        source += line;
        source += '\n';
    }
    return source;
}

GLuint compileShader(GLuint type, const char* filename){
    std::string source = readFile(filename);

    if (source.empty()){
        return 0;
    }

    const char* sourceCStr = source.c_str();
    GLuint shader = glCreateShader(type);

    glShaderSource(shader, 1, &sourceCStr, nullptr);
    glCompileShader(shader);

    return shader;
}

ShaderProgram::ShaderProgram(const char* vertexFilename, const char* fragmentFilename){
    GLuint vertexShader = compileShader(GL_VERTEX_SHADER, vertexFilename);
    if (vertexShader == 0){
        return;
    }

    GLuint fragmentShader = compileShader(GL_FRAGMENT_SHADER, fragmentFilename);

    if (fragmentShader == 0) {
        glDeleteShader(vertexShader);
        return;
    }

    ID = glCreateProgram();
    glAttachShader(ID, vertexShader);
    glAttachShader(ID, fragmentShader);
    glLinkProgram(ID);
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}
ShaderProgram::~ShaderProgram(){
    if (ID != 0){
        glDeleteProgram(ID);
    }
}
void ShaderProgram::use() const{
    if (ID != 0){
        glUseProgram(ID);
    }
}
GLint ShaderProgram::getUniformLocation(const char* name) const{
    return glGetUniformLocation(ID, name);
}