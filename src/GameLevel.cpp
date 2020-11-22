#include "GameLevel.h"
#include <iostream>
#include <fstream>
#include <sstream>

void GameLevel::Load(const char *file) {
    this->Cubes.clear();

    // load from file
    unsigned int cubeCode;
    GameLevel level;
    std::string line;
    std::ifstream fstream(file);

    if(fstream)
    {
        fstream >> this->levelSize;
        std::getline(fstream, line);
        while(std::getline(fstream, line))
        {
            std::istringstream sstream(line);
            std::vector<unsigned int> row;
            while(sstream >> cubeCode)
                    row.push_back(cubeCode);

            cubeData.push_back(row);
        }

        if(cubeData.size() > 0)
            this->init();
    }else
    {
        //greska
    }
}

void GameLevel::Draw(SpriteRenderer &Renderer) {
    for(GameObject &cube : this->Cubes)
        cube.Draw(Renderer);
}

bool GameLevel::isCompleted() {
    for(unsigned int i = 0; i < levelSize; i++)
    {
        for(unsigned int j = 0; j < levelSize; j++)
        {
            if(cubeData[i][j] == 2){
                return false;
            }
        }
    }
    return true;
}

void GameLevel::init()
{
    float unitSize = 1.0f;
    cubeData.resize(levelSize);
    for(unsigned int i = 0; i < levelSize; i++)
        cubeData[i].resize(levelSize);

    for(unsigned int i = 0; i < levelSize; i++)
    {
        for(unsigned int j = 0; j < levelSize; j++)
        {
            /*
                9 for borders
                5 for folk
                4 for done boxes
                3 for normal boxes
                2 for empty spots
                1 for normal floor
                0 for free space
            */
            if(cubeData[i][j] == 9) { //zid
                glm::vec3 pos(i * unitSize, j * unitSize, 0.0f);
                glm::vec3 size(unitSize);
                GameObject obj(pos, size, ResourceManager::GetTexture("wall"), glm::vec3(1.0f));
                this->Cubes.push_back(obj);
                pos = glm::vec3(i * unitSize, j * unitSize, -unitSize);
                size = glm::vec3(unitSize);
                obj = GameObject(pos, size, ResourceManager::GetTexture("floor"), glm::vec3(1.0f));
                this->Cubes.push_back(obj);
            }else if(cubeData[i][j] == 5){ //cikica
                glm::vec3 pos(i * unitSize, j * unitSize, 0.0f);
                glm::vec3 size(unitSize);
                GameObject obj(pos, size, ResourceManager::GetTexture("folk"), glm::vec3(1.0f));
                this->Cubes.push_back(obj);

                pos = glm::vec3(i * unitSize, j * unitSize, -unitSize);
                size = glm::vec3(unitSize);
                obj = GameObject(pos, size, ResourceManager::GetTexture("floor"), glm::vec3(1.0f));
                this->Cubes.push_back(obj);
            }else if(cubeData[i][j] == 4){ //done box
                glm::vec3 pos(i * unitSize, j * unitSize, 0.0f);
                glm::vec3 size(unitSize);
                GameObject obj(pos, size, ResourceManager::GetTexture("box"), glm::vec3(0.0f, 1.0f, 0.0f));
                this->Cubes.push_back(obj);

                pos = glm::vec3(i * unitSize, j * unitSize, -unitSize);
                size = glm::vec3(unitSize);
                obj = GameObject(pos, size, ResourceManager::GetTexture("floor"), glm::vec3(1.0f));
                this->Cubes.push_back(obj);
            }else if(cubeData[i][j] == 3){ //obican box
                glm::vec3 pos(i * unitSize, j * unitSize, 0.0f);
                glm::vec3 size(unitSize);
                GameObject obj(pos, size, ResourceManager::GetTexture("box"), glm::vec3(1.0f));
                this->Cubes.push_back(obj);

                pos = glm::vec3(i * unitSize, j * unitSize, -unitSize);
                size = glm::vec3(unitSize);
                obj = GameObject(pos, size, ResourceManager::GetTexture("floor"), glm::vec3(1.0f));
                this->Cubes.push_back(obj);
            }else if(cubeData[i][j] == 2){ //ciljno polje
                glm::vec3 pos(i * unitSize, j * unitSize, -unitSize);
                glm::vec3 size(unitSize);
                GameObject obj(pos, size, ResourceManager::GetTexture("floor"), glm::vec3(1.0f, 0.0f, 0.0f));
                this->Cubes.push_back(obj);
            }else if(cubeData[i][j] == 1){ // pod
                glm::vec3 pos(i * unitSize, j * unitSize, -unitSize);
                glm::vec3 size(unitSize);
                GameObject obj(pos, size, ResourceManager::GetTexture("floor"), glm::vec3(1.0f));
                this->Cubes.push_back(obj);
            }
        }
    }
}
