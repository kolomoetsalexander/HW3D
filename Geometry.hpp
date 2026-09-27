#pragma once
#include <glad/glad.h>
#include <glm/glm.hpp>
struct Geometry{
    GLuint VAO;
    GLuint VBO;
    GLuint EBO;
    int indexCount;
};
glm::vec3 calculateNormal(const glm::vec3& A, const glm::vec3& B, const glm::vec3& C);
Geometry createTriangule(const glm::vec3& A, const glm::vec3& B, const glm::vec3& C);