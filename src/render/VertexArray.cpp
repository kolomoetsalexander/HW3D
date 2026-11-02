#include "VertexArray.hpp"

VertexArray::VertexArray(){
    glGenVertexArrays(1, &VAO);
}
VertexArray::~VertexArray(){
    if(VAO != 0){
        glDeleteVertexArrays(1, &VAO);
    }
}
void VertexArray::bind() const{
    glBindVertexArray(VAO);
}