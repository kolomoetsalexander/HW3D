#pragma once
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <vector>
struct Triangle{
    glm::vec3 A, B, C;
};
struct Geometry{
    GLuint VAO;
    GLuint VBO;
    GLuint EBO;
    int vertexCount;
};
glm::vec3 calculateNormal(const glm::vec3& A, const glm::vec3& B, const glm::vec3& C);
Geometry createScene(const std::vector<Triangle>& triangles, const std::vector<bool>& intersects);