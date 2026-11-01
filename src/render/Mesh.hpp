#pragma once
#include <glad/glad.h>
#include "geometry/Triangle.hpp"
#include <vector>

class Mesh{
public:
    Mesh(const std::vector<Triangle>& triangles, const std::vector<bool>& intersects);
    ~Mesh();
    //copy forbidden
    Mesh(const Mesh&) = delete;
    //assignment forbidden
    Mesh& operator=(const Mesh&) = delete;
    void draw() const;

private:
    GLuint VAO = 0;
    GLuint VBO = 0;
    GLsizei vertexCount = 0;

};
glm::vec3 calculateNormal(const glm::vec3& A, const glm::vec3& B, const glm::vec3& C);
Mesh createScene(const std::vector<Triangle>& triangles, const std::vector<bool>& intersects);
