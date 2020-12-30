#ifndef PROJECT_BASE_SPRITERENDERERSKYBOX_H
#define PROJECT_BASE_SPRITERENDERERSKYBOX_H

#include <learnopengl/camera.h>
#include <learnopengl/shader.h>

class SpriteRendererSkyBox {
public:
    SpriteRendererSkyBox(Shader shader, Camera &cam);
    ~SpriteRendererSkyBox();

    void setCubeMapTextureId(unsigned int cubeMapTextureId);

    void Draw();
private:
    Shader shader;
    Camera &camera;
    unsigned int cubeMapTextureID;

    unsigned int skyboxVAO;
    void init_data();
};


#endif //PROJECT_BASE_SPRITERENDERERSKYBOX_H
