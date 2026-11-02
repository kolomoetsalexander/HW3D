#include "VertexBuffer.hpp"

VertexBuffer::VertexBuffer(){
    glGenBuffers(1, &VBO);
}
VertexBuffer::~VertexBuffer(){
    if(VBO != 0){
        glDeleteBuffers(1, &VBO);
    }
}
void VertexBuffer::bind() const{
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
}
