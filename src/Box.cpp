#include "Box.h"

Box::Box() : Position(0.0f), Size(0.0f), Color(1.0f), diffuse(), specular(), alpha(false) {

}

Box::Box(glm::vec3 pos, glm::vec3 size, Texture2D diffuse, Texture2D specular, glm::vec3 color, bool alpha) :
        Position(pos), Size(size), Color(color), diffuse(diffuse), specular(specular), alpha(alpha){}

void Box::Draw(SpriteRendererBox &renderer, std::vector<glm::vec3> lightPositions) {
    renderer.DrawSpriteBox(lightPositions, diffuse, specular, Position, Size, 0.0f, Color, alpha);
}
