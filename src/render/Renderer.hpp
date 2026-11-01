#pragma once
#include <glad/glad.h>
#include <glm/glm.hpp>
#include "Camera.hpp"
#include "Mesh.hpp"
#include "ShaderProgram.hpp"

class Renderer{
public:
    Renderer(Mesh& mesh, ShaderProgram& shader);
    void render(const Camera& camera);
private:
    Mesh& mesh;
    ShaderProgram& shader;
    
    glm::mat4 model;
    glm::mat4 perspective;
    glm::vec3 lightPos;
    GLint modelLoc;
    GLint viewLoc;
    GLint perspectiveLoc;
    GLint lightPosLoc;
    GLint viewPosLoc;
};