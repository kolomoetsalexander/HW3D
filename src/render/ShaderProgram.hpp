#pragma once
#include <glad/glad.h>

class ShaderProgram{
public:
    ShaderProgram(const char* vertexFilename, const char* fragmentFilename);
    //rule of three
    ~ShaderProgram();
    ShaderProgram(const ShaderProgram&) = delete;
    ShaderProgram& operator=(const ShaderProgram&) = delete;

    void use() const;
    GLint getUniformLocation(const char* name) const;

private:
    GLuint ID = 0;
};