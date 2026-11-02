#pragma once
#include <glad/glad.h>

class VertexArray{
public:
    VertexArray();
    ~VertexArray();
    VertexArray(const VertexArray&) = delete;
    VertexArray& operator=(const VertexArray&) = delete;

    void bind() const;
private:
    GLuint VAO = 0;
};