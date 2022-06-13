#pragma once
#ifndef PROJECT_BASE_MODELRENDERERTORCH_H
#define PROJECT_BASE_MODELRENDERERTORCH_H

#include <learnopengl/camera.h>
#include <learnopengl/model.h>
#include <learnopengl/shader.h>


class ModelRendererTorch
{
public:
  ModelRendererTorch(Shader shader, Camera &camera);
  ~ModelRendererTorch();

  void
  Draw(Model model, glm::vec3 position, glm::vec3 size, glm::vec3 rotation,
       float angle);

private:
  Shader shader;
  Camera &camera;
};


#endif // PROJECT_BASE_MODELRENDERERTORCH_H
