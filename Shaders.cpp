#include "Shaders.hpp"
#include <fstream>
#include <string>

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