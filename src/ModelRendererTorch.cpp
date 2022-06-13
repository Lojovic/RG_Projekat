#include "ModelRendererTorch.h"

ModelRendererTorch::ModelRendererTorch(Shader shader, Camera& camera)
    : camera(camera) {
  this->shader = shader;
}

ModelRendererTorch::~ModelRendererTorch() = default;

// an abstraction for rendering the torches
void
ModelRendererTorch::Draw(Model model, glm::vec3 position, glm::vec3 size,
                         glm::vec3 rotation, float angle) {
  this->shader.Use();

  glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom),
                                          800.0f / 600.0f, 0.1f, 100.0f);
  glm::mat4 view = camera.GetViewMatrix();
  this->shader.SetMatrix4("projection", projection);
  this->shader.SetMatrix4("view", view);

  // render the loaded model
  glm::mat4 modelMatrix = glm::mat4(1.0f);
  modelMatrix = glm::translate(modelMatrix, position);
  modelMatrix = glm::rotate(modelMatrix, glm::radians(angle), rotation);
  modelMatrix = glm::scale(modelMatrix, size);
  this->shader.SetMatrix4("model", modelMatrix);
  model.Draw(this->shader);
}
