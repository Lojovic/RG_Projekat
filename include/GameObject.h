#pragma once
#ifndef PROJECT_BASE_GAMEOBJECT_H
#define PROJECT_BASE_GAMEOBJECT_H

#include "SpriteRenderer.h"
#include "Texture.h"
#include <glad/glad.h>
#include <glm/glm.hpp>

class GameObject
{
public:
  glm::vec3 Position, Size, Color;
  Texture2D Sprite;

  GameObject();
  GameObject(glm::vec3 pos, glm::vec3 size, Texture2D sprite,
             glm::vec3 color = glm::vec3(1.0f));

  virtual void
  Draw(SpriteRenderer &renderer, std::vector<glm::vec3> lightPositions);
};


#endif // PROJECT_BASE_GAMEOBJECT_H
