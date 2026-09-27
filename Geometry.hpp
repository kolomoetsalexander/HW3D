#pragma once
#include <glad/glad.h>
struct Geometry{
    GLuint VAO;
    GLuint VBO;
    GLuint EBO;
    int indexCount;
};
Geometry createFigure();