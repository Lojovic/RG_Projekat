#pragma once
#ifndef PROJECT_BASE_SPRITERENDERERBOX_H
#define PROJECT_BASE_SPRITERENDERERBOX_H

#include "Shader.h"
#include "Texture.h"
#include <learnopengl/camera.h>

class SpriteRendererBox {
public:
    SpriteRendererBox(Shader shader, Camera& camera);
    ~SpriteRendererBox();

    void DrawSpriteBox(std::vector<glm::vec3> pointLightPositions, Texture2D diffuse, Texture2D specular, glm::vec3 position,
                    glm::vec3 size = glm::vec3(10.0f, 10.0f, 10.0f),float rotate = 0.0f, glm::vec3 color = glm::vec3(1.0f));

private:
    Shader  shader;
    Camera &camera;
    unsigned int VAO;

    void initRenderData();
};


#endif //PROJECT_BASE_SPRITERENDERERBOX_H
