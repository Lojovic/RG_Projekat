#include "GameObject.h"

GameObject::GameObject() : Position(0.0f), Size(0.0f), Color(1.0f), Sprite(){ }

GameObject::GameObject(glm::vec3 pos, glm::vec3 size, Texture2D sprite, glm::vec3 color)
: Position(pos), Size(size), Color(color), Sprite(sprite){}

void GameObject::Draw(SpriteRenderer &renderer, std::vector<glm::vec3> lightPositions) {
    renderer.DrawSprite(lightPositions,this->Sprite, this->Position, this->Size, 0.0f,  this->Color);
}
