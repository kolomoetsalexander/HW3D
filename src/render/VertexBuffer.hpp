#pragma once
#include <glad/glad.h>

class VertexBuffer{
public:
    VertexBuffer();
    ~VertexBuffer();
    VertexBuffer(const VertexBuffer&) = delete;
    VertexBuffer& operator=(const VertexBuffer&) = delete;

    void bind() const;
private:
    GLuint VBO = 0;
};