#include "Geometry.hpp"
glm::vec3 calculateNormal(const glm::vec3& A, const glm::vec3& B, const glm::vec3& C){
    glm::vec3 AB = B - A;
    glm::vec3 AC = C - A;
    glm::vec3 normal = glm::cross(AB, AC);
    return glm::normalize(normal);
}
Geometry createScene(const std::vector<Triangle>& triangles, const std::vector<bool>& intersects){
    std::vector<float> vertices;
    vertices.reserve(triangles.size() * 3 * 7);
    for (size_t i = 0; i < triangles.size(); ++i){
        const Triangle& t = triangles[i];
        glm::vec3 normal = calculateNormal(t.A, t.B, t.C);
        // 
        float isRed = (i < intersects.size() && intersects[i]) ? 1.0f : 0.0f;

        const glm::vec3* pts[3] = { &t.A, &t.B, &t.C };
        for (int v = 0; v < 3; ++v){
            vertices.push_back(pts[v]->x);
            vertices.push_back(pts[v]->y);
            vertices.push_back(pts[v]->z);
            vertices.push_back(normal.x);
            vertices.push_back(normal.y);
            vertices.push_back(normal.z);
            vertices.push_back(isRed);
        }
    }
    Geometry geometry;
    glGenVertexArrays(1, &geometry.VAO);
    glBindVertexArray(geometry.VAO);
    glGenBuffers(1, &geometry.VBO);
    glBindBuffer(GL_ARRAY_BUFFER, geometry.VBO);
    glBufferData(
        GL_ARRAY_BUFFER,
        vertices.size() * sizeof(float),
        vertices.data(),
        GL_STATIC_DRAW
    );
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1,3, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, 1, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);
    geometry.vertexCount = static_cast<int>(triangles.size() * 3);
    return geometry;
}