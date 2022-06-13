#include "SpriteRenderer.h"
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
#include <learnopengl/camera.h>


SpriteRenderer::SpriteRenderer(Shader shader, Camera& cam) : camera(cam) {
  this->shader = shader;
  this->initRenderData();
}

SpriteRenderer::~SpriteRenderer() = default;

void
SpriteRenderer::DrawSprite(std::vector<glm::vec3> pointLightPositions,
                           Texture2D texture, glm::vec3 position,
                           glm::vec3 size, float rotation, glm::vec3 color) {
  // we activate and bind the given texture
  glActiveTexture(GL_TEXTURE0);
  texture.Bind();

  // activating the shader abstraction and setting up the uniforms
  this->shader.Use();
  this->shader.SetVector3f("viewPos", this->camera.Position);
  this->shader.SetFloat("material.shininess", 32.0f);
  this->shader.SetInteger("number_of_lights", (int)pointLightPositions.size());

  for (unsigned int i = 0; i < pointLightPositions.size(); i++) {
    std::string tmp = "pointLights[" + std::to_string(i) + "]";

    this->shader.SetVector3f((tmp + ".position").c_str(),
                             pointLightPositions[i]);
    this->shader.SetVector3f((tmp + ".diffuse").c_str(), 0.8f, 0.8f, 0.8f);
    this->shader.SetVector3f((tmp + ".specular").c_str(), 1.0f, 1.0f, 1.0f);
    this->shader.SetVector3f((tmp + ".ambient").c_str(), 0.05f, 0.05f, 0.05f);
    this->shader.SetFloat((tmp + ".constant").c_str(), 1.0f);
    this->shader.SetFloat((tmp + ".linear").c_str(), 0.09);
    this->shader.SetFloat((tmp + ".quadratic").c_str(), 0.032);
  }

  glm::mat4 model = glm::mat4(1.0f);
  glm::mat4 view = glm::mat4(1.0f);
  glm::mat4 projection = glm::mat4(1.0f);

  projection = glm::perspective(glm::radians(this->camera.Zoom),
                                800.0f / 600.0f, 0.1f, 100.0f);
  this->shader.SetMatrix4("projection", projection);

  view = this->camera.GetViewMatrix();
  this->shader.SetMatrix4("view", view);

  // T -> R -> S
  model = glm::translate(model, position);
  model =
      glm::rotate(model, glm::radians(rotation), glm::vec3(1.0f, 0.0f, 0.0f));
  model = glm::scale(model, size);
  this->shader.SetMatrix4("model", model);

  // binding the VAO and drawing the object
  glBindVertexArray(this->VAO);
  glDrawArrays(GL_TRIANGLES, 0, 36);

  // unbinding the VAO
  glBindVertexArray(0);
}

void
SpriteRenderer::initRenderData() {
  unsigned int VBO;
  float vertices[] = {
      // positions          // normals           // texture coords
      -0.5f, -0.5f, -0.5f, 0.0f,  0.0f,  -1.0f, 0.0f,  0.0f,  0.5f,  -0.5f,
      -0.5f, 0.0f,  0.0f,  -1.0f, 1.0f,  0.0f,  0.5f,  0.5f,  -0.5f, 0.0f,
      0.0f,  -1.0f, 1.0f,  1.0f,  0.5f,  0.5f,  -0.5f, 0.0f,  0.0f,  -1.0f,
      1.0f,  1.0f,  -0.5f, 0.5f,  -0.5f, 0.0f,  0.0f,  -1.0f, 0.0f,  1.0f,
      -0.5f, -0.5f, -0.5f, 0.0f,  0.0f,  -1.0f, 0.0f,  0.0f,

      -0.5f, -0.5f, 0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,  0.5f,  -0.5f,
      0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  0.0f,  0.5f,  0.5f,  0.5f,  0.0f,
      0.0f,  1.0f,  1.0f,  1.0f,  0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
      1.0f,  1.0f,  -0.5f, 0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  1.0f,
      -0.5f, -0.5f, 0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,

      -0.5f, 0.5f,  0.5f,  -1.0f, 0.0f,  0.0f,  1.0f,  0.0f,  -0.5f, 0.5f,
      -0.5f, -1.0f, 0.0f,  0.0f,  1.0f,  1.0f,  -0.5f, -0.5f, -0.5f, -1.0f,
      0.0f,  0.0f,  0.0f,  1.0f,  -0.5f, -0.5f, -0.5f, -1.0f, 0.0f,  0.0f,
      0.0f,  1.0f,  -0.5f, -0.5f, 0.5f,  -1.0f, 0.0f,  0.0f,  0.0f,  0.0f,
      -0.5f, 0.5f,  0.5f,  -1.0f, 0.0f,  0.0f,  1.0f,  0.0f,

      0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,  0.5f,  0.5f,
      -0.5f, 1.0f,  0.0f,  0.0f,  1.0f,  1.0f,  0.5f,  -0.5f, -0.5f, 1.0f,
      0.0f,  0.0f,  0.0f,  1.0f,  0.5f,  -0.5f, -0.5f, 1.0f,  0.0f,  0.0f,
      0.0f,  1.0f,  0.5f,  -0.5f, 0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
      0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

      -0.5f, -0.5f, -0.5f, 0.0f,  -1.0f, 0.0f,  0.0f,  1.0f,  0.5f,  -0.5f,
      -0.5f, 0.0f,  -1.0f, 0.0f,  1.0f,  1.0f,  0.5f,  -0.5f, 0.5f,  0.0f,
      -1.0f, 0.0f,  1.0f,  0.0f,  0.5f,  -0.5f, 0.5f,  0.0f,  -1.0f, 0.0f,
      1.0f,  0.0f,  -0.5f, -0.5f, 0.5f,  0.0f,  -1.0f, 0.0f,  0.0f,  0.0f,
      -0.5f, -0.5f, -0.5f, 0.0f,  -1.0f, 0.0f,  0.0f,  1.0f,

      -0.5f, 0.5f,  -0.5f, 0.0f,  1.0f,  0.0f,  0.0f,  1.0f,  0.5f,  0.5f,
      -0.5f, 0.0f,  1.0f,  0.0f,  1.0f,  1.0f,  0.5f,  0.5f,  0.5f,  0.0f,
      1.0f,  0.0f,  1.0f,  0.0f,  0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
      1.0f,  0.0f,  -0.5f, 0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  0.0f,
      -0.5f, 0.5f,  -0.5f, 0.0f,  1.0f,  0.0f,  0.0f,  1.0f};

  glGenVertexArrays(1, &this->VAO);
  glGenBuffers(1, &VBO);

  glBindVertexArray(this->VAO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  // postition atribute
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float),
                        (void*)nullptr);
  glEnableVertexAttribArray(0);
  // normals atribute
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float),
                        (void*)(3 * sizeof(float)));
  glEnableVertexAttribArray(1);
  // tex coords atribute
  glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float),
                        (void*)(6 * sizeof(float)));
  glEnableVertexAttribArray(2);

  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);
}
