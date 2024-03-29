#pragma once
#ifndef PROJECT_BASE_GAMELEVEL_H
#define PROJECT_BASE_GAMELEVEL_H
#include <unordered_map>
#include <vector>

#include "Box.h"
#include "GameObject.h"
#include "ResourceManager.h"
#include "SpriteRenderer.h"
#include <GLFW/glfw3.h>
#include <fstream>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <iostream>
#include <sstream>

class GameLevel
{
public:
  std::vector<GameObject> Cubes;
  std::vector<Box> Boxes;
  std::vector<Box> BlendBoxes;
  std::vector<glm::vec3> Lights;
  GameLevel() {}
  // Load level from file
  void
  Load(const char *file);
  // render lvl
  void
  Draw(SpriteRenderer &Renderer, SpriteRendererBox &BoxRenderer);
  // check if level is completed (all cubes are on right position)
  bool
  isCompleted();
  bool
  move(unsigned int direction);
  bool
  update();

private:
  std::vector<std::vector<unsigned int>> cubeData;
  std::vector<std::vector<unsigned int>> goalSquareData;
  unsigned int levelSize;
  unsigned int folkX;
  unsigned int folkY;
  void
  init();
};


#endif // PROJECT_BASE_GAMELEVEL_H
