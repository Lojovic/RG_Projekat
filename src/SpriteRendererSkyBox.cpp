#include "SpriteRendererSkyBox.h"

SpriteRendererSkyBox::SpriteRendererSkyBox(Shader shader, Camera& cam)
    : camera(cam) {
  this->shader = shader;
  this->cubeMapTextureID = 0;
  init_data();
}

SpriteRendererSkyBox::~SpriteRendererSkyBox() = default;

void
SpriteRendererSkyBox::Draw() {
  glDepthFunc(GL_LEQUAL);
  this->shader.Use();
  glm::mat4 view = glm::mat4(glm::mat3(this->camera.GetViewMatrix()));
  glm::mat4 projection = this->camera.GetProjectionMatrix();
  this->shader.SetMatrix4("view", view);
  this->shader.SetMatrix4("projection", projection);
  // draw skybox cube
  glBindVertexArray(this->skyboxVAO);
  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_CUBE_MAP, cubeMapTextureID);
  glDrawArrays(GL_TRIANGLES, 0, 36);
  glBindVertexArray(0);
  glDepthFunc(GL_LESS);
}

void
SpriteRendererSkyBox::init_data() {

  unsigned int skyboxVBO;
  float skyboxVertices[] = {
      // positions
      -1.0f, 1.0f,  -1.0f, -1.0f, -1.0f, -1.0f, 1.0f,  -1.0f, -1.0f,
      1.0f,  -1.0f, -1.0f, 1.0f,  1.0f,  -1.0f, -1.0f, 1.0f,  -1.0f,

      -1.0f, -1.0f, 1.0f,  -1.0f, -1.0f, -1.0f, -1.0f, 1.0f,  -1.0f,
      -1.0f, 1.0f,  -1.0f, -1.0f, 1.0f,  1.0f,  -1.0f, -1.0f, 1.0f,

      1.0f,  -1.0f, -1.0f, 1.0f,  -1.0f, 1.0f,  1.0f,  1.0f,  1.0f,
      1.0f,  1.0f,  1.0f,  1.0f,  1.0f,  -1.0f, 1.0f,  -1.0f, -1.0f,

      -1.0f, -1.0f, 1.0f,  -1.0f, 1.0f,  1.0f,  1.0f,  1.0f,  1.0f,
      1.0f,  1.0f,  1.0f,  1.0f,  -1.0f, 1.0f,  -1.0f, -1.0f, 1.0f,

      -1.0f, 1.0f,  -1.0f, 1.0f,  1.0f,  -1.0f, 1.0f,  1.0f,  1.0f,
      1.0f,  1.0f,  1.0f,  -1.0f, 1.0f,  1.0f,  -1.0f, 1.0f,  -1.0f,

      -1.0f, -1.0f, -1.0f, -1.0f, -1.0f, 1.0f,  1.0f,  -1.0f, -1.0f,
      1.0f,  -1.0f, -1.0f, -1.0f, -1.0f, 1.0f,  1.0f,  -1.0f, 1.0f};

  glGenVertexArrays(1, &this->skyboxVAO);
  glGenBuffers(1, &skyboxVBO);
  glBindVertexArray(this->skyboxVAO);
  glBindBuffer(GL_ARRAY_BUFFER, skyboxVBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxVertices), &skyboxVertices,
               GL_STATIC_DRAW);
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float),
                        (void*)nullptr);

  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);
}

void
SpriteRendererSkyBox::setCubeMapTextureId(unsigned int cubeMapTextureId) {
  cubeMapTextureID = cubeMapTextureId;
}
