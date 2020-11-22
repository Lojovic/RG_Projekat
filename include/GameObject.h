#ifndef PROJECT_BASE_GAMEOBJECT_H
#define PROJECT_BASE_GAMEOBJECT_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include "Texture.h"
#include "SpriteRenderer.h"

class GameObject {
public:
    glm::vec3 Position, Size, Color;
    Texture2D Sprite;

    GameObject();
    GameObject(glm::vec3 pos, glm::vec3 size, Texture2D sprite, glm::vec3 color = glm::vec3(1.0f));

    virtual void Draw(SpriteRenderer &renderer);
};


#endif //PROJECT_BASE_GAMEOBJECT_H
