#pragma once
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <vector>
#include "geometry/Triangle.hpp"
struct Geometry{
    GLuint VAO;
    GLuint VBO;
    GLuint EBO;
    int vertexCount;
};