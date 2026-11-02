#include "VertexBuffer.hpp"

VertexBuffer::VertexBuffer(){
    glGenVertexArrays(1, &VBO);
}
VertexBuffer::~VertexBuffer(){
    if(VBO != 0){
        glDeleteVertexArrays(1, &VBO);
    }
}
void VertexBuffer::bind() const{
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
}
