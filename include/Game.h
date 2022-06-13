#pragma once
#ifndef PROJECT_BASE_GAME_H
#define PROJECT_BASE_GAME_H
#include "GameLevel.h"
#include "ModelRendererTorch.h"
#include "ResourceManager.h"
#include "SpriteRenderer.h"
#include "SpriteRendererBox.h"
#include "SpriteRendererSkyBox.h"
#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <learnopengl/camera.h>
#include <learnopengl/filesystem.h>

class Game
{
public:
  Game(unsigned int width, unsigned int height);
  ~Game();
  std::vector<GameLevel> Levels;
  unsigned int levelID;
  bool GameKeys[1024];
  unsigned int width, height;
  void
  init();
  void
  processInput(float deltaTime);
  bool cameraLock = true;
  // void update(float deltaTime);
  std::unordered_map<unsigned int, std::string> pathMap;
  void
  render();
  Camera&
  getCamera();

private:
  unsigned int numberOfLevels = 3;

  Camera camera;
};


#endif // PROJECT_BASE_GAME_H
