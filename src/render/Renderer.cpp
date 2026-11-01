#include "Renderer.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
Renderer::Renderer(Mesh& mesh, ShaderProgram& shader):
    mesh(mesh),
    shader(shader),
    model(1.0f),
    perspective(glm::perspective(glm::radians(70.0f), 3200.0f / 2000.0f, 0.1f, 200.0f)), lightPos(5.0f, 8.0f, 5.0f){
        modelLoc = shader.getUniformLocation("model");
        viewLoc = shader.getUniformLocation("view");
        perspectiveLoc = shader.getUniformLocation("perspective");
        lightPosLoc = shader.getUniformLocation("lightPos");
        viewPosLoc = shader.getUniformLocation("viewPos");
    }
void Renderer::render(const Camera& camera){
    glm::mat4 view = camera.getViewMatrix();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    shader.use();
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
    glUniformMatrix4fv(perspectiveLoc, 1, GL_FALSE, glm::value_ptr(perspective));
    glUniform3fv(lightPosLoc, 1, glm::value_ptr(lightPos));
    glUniform3fv(viewPosLoc, 1, glm::value_ptr(camera.getPosition()));
    mesh.draw();
}