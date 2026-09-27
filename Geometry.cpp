#include "Geometry.hpp"
glm::vec3 calculateNormal(const glm::vec3& A, const glm::vec3& B, const glm::vec3& C){
    glm::vec3 AB = B - A;
    glm::vec3 AC = C - A;
    glm::vec3 normal = glm::cross(AB, AC);
    return glm::normalize(normal);
}
Geometry createTriangule(const glm::vec3& A, const glm::vec3& B, const glm::vec3& C){
    glm::vec3 normal = calculateNormal(A, B, C);
    float vertices[] =
    {
        A.x, A.y, A.z, normal.x, normal.y, normal.z,
        B.x, B.y, B.z, normal.x, normal.y, normal.z,
        C.x, C.y, C.z, normal.x, normal.y, normal.z
    };
    unsigned int indices[] =
    {
        0, 1, 2
    };
    
    Geometry geometry;
    glGenVertexArrays(1, &geometry.VAO);
    glBindVertexArray(geometry.VAO);
    glGenBuffers(1, &geometry.VBO);
    glBindBuffer(GL_ARRAY_BUFFER, geometry.VBO);
    glBufferData(
        GL_ARRAY_BUFFER,
        sizeof(vertices),
        vertices,
        GL_STATIC_DRAW
    );

    glGenBuffers(1, &geometry.EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, geometry.EBO);
    glBufferData(
        GL_ELEMENT_ARRAY_BUFFER,
        sizeof(indices),
        indices,
        GL_STATIC_DRAW
    );

    glVertexAttribPointer(
        0,
        3,
        GL_FLOAT,
        GL_FALSE,
        6 * sizeof(float),
        (void*)0
    );
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(
        1,
        3,
        GL_FLOAT,
        GL_FALSE,
        6 * sizeof(float),
        (void*)(3 * sizeof(float))
    );
    glEnableVertexAttribArray(1);
    geometry.indexCount = 3;
    return geometry;
}