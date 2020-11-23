#pragma once
#ifndef PROJECT_BASE_GAMELEVEL_H
#define PROJECT_BASE_GAMELEVEL_H
#include <vector>
#include <unordered_map>

#include <glad/glad.h>
#include <glm/glm.hpp>

#include "GameObject.h"
#include "SpriteRenderer.h"
#include "ResourceManager.h"

class GameLevel {
public:
    std::vector<GameObject> Cubes;
    GameLevel() {}
    //Load level from file
    void Load(const char *file);
    //render lvl
    void Draw(SpriteRenderer &Renderer);
    //check if level is completed (all cubes are on right position)
    bool isCompleted();
    bool move(unsigned int direction);
    bool update();

private:
    std::vector<std::vector<unsigned int>> cubeData;
    std::vector<std::vector<unsigned int>> goalSquareData;
    unsigned int levelSize;
    unsigned int folkX;
    unsigned int folkY;
    void init();
};


#endif //PROJECT_BASE_GAMELEVEL_H
