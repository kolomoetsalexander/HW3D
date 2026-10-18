#pragma once
#include <glad/glad.h>
GLuint compileShader(GLuint type, const char* filename);
GLuint createShaderProgram(const char* vertexFilename, const char* fragmentFilename);