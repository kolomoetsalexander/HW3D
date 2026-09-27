#include "Geometry.hpp"
Geometry createFigure(){
    float vertices[] =
    {
        0.0f,  0.6f,  0.0f,
        -0.6f, -0.4f,  0.4f,
        0.6f, -0.4f,  0.4f,
        0.0f, -0.4f, -0.6f
    };
    unsigned int indices[] =
    {
        0, 1, 2,
        0, 3, 1,
        0, 2, 3,
        1, 3, 2
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
        3 * sizeof(float),
        (void*)0
    );
    glEnableVertexAttribArray(0);
    geometry.indexCount = 12;
    return geometry;
}