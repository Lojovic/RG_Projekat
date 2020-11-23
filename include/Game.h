#pragma once
#ifndef PROJECT_BASE_GAME_H
#define PROJECT_BASE_GAME_H
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <learnopengl/camera.h>
#include "GameLevel.h"

class Game {
public:
    Game(unsigned int width, unsigned int height);
    ~Game();
    std::vector<GameLevel> Levels;
    unsigned int levelID;
    bool GameKeys[1024];
    unsigned int width, height;
    void init();
    void processInput(float deltaTime);
    //void update(float deltaTime);
    void render();
    Camera &getCamera();
private:
    std::unordered_map<unsigned int, std::string> pathMap;
    unsigned int numberOfLevels = 3;
    Camera camera;
};


#endif //PROJECT_BASE_GAME_H
