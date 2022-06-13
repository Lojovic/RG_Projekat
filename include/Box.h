#pragma once
#ifndef PROJECT_BASE_BOX_H
#define PROJECT_BASE_BOX_H

#include "SpriteRendererBox.h"
#include "Texture.h"
#include <glad/glad.h>
#include <glm/glm.hpp>

class Box
{
public:
  glm::vec3 Position, Size, Color;
  bool alpha;
  Texture2D diffuse;
  Texture2D specular;

  Box();
  Box(glm::vec3 pos, glm::vec3 size, Texture2D diffuse, Texture2D specular,
      glm::vec3 color = glm::vec3(1.0f), bool alpha = false);

  virtual void
  Draw(SpriteRendererBox& renderer, std::vector<glm::vec3> lightPositions);
};


#endif // PROJECT_BASE_BOX_H
