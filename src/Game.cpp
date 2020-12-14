#include "Game.h"
#include "ResourceManager.h"
#include "SpriteRenderer.h"
#include "SpriteRendererBox.h"
#include "learnopengl/filesystem.h"

SpriteRenderer *Renderer;
SpriteRendererBox *BoxRenderer;

Game::Game(unsigned int width, unsigned int height) : levelID(0){
    this->width = width;
    this->height = height;
    this->camera.Position = glm::vec3(3.0f, 3.0f, 10.0f);
    this->pathMap[0] = "resources/levels/1.txt";
    this->pathMap[1] = "resources/levels/2.txt";
    this->pathMap[2] = "resources/levels/3.txt";
}

Game::~Game() {
    delete Renderer;
}

void Game::init() {
    //load shader
    ResourceManager::LoadShader(FileSystem::getPath("resources/shaders/vertexShader.vs.glsl").c_str(),
                                FileSystem::getPath("resources/shaders/fragmentShader.fs.glsl").c_str(), nullptr, "sprite");
    ResourceManager::LoadShader(FileSystem::getPath("resources/shaders/vertexShader.vs.glsl").c_str(),
                                FileSystem::getPath("resources/shaders/fragmentShaderBox.fs.glsl").c_str(), nullptr, "sprite_box");

    //configure shader
    //only once has to be done
    ResourceManager::GetShader("sprite").Use().SetInteger("material.diffuse", 0);
    ResourceManager::GetShader("sprite").Use().SetVector3f("material.specular", glm::vec3(0.2f));

    ResourceManager::GetShader("sprite_box").Use().SetInteger("material.diffuse", 0);
    ResourceManager::GetShader("sprite_box").Use().SetInteger("material.specular", 1);

    //set render-specific controls
    Renderer = new SpriteRenderer(ResourceManager::GetShader("sprite"), this->camera);
    BoxRenderer = new SpriteRendererBox(ResourceManager::GetShader("sprite_box"), this->camera);

    //load texture
    ResourceManager::LoadTexture(FileSystem::getPath("resources/textures/container.png").c_str(), true, "box");
    ResourceManager::LoadTexture(FileSystem::getPath("resources/textures/awesomeface.png").c_str(), true, "folk");
    ResourceManager::LoadTexture(FileSystem::getPath("resources/textures/bricks.jpg").c_str(), false, "wall");
    ResourceManager::LoadTexture(FileSystem::getPath("resources/textures/floor.png").c_str(), false, "floor");
    ResourceManager::LoadTexture(FileSystem::getPath("resources/textures/target.jpg").c_str(), false, "target");
    ResourceManager::LoadTexture(FileSystem::getPath("resources/textures/container_specular.png").c_str(), true, "box_specular");

    GameLevel one;
    GameLevel two;
    GameLevel three;

    one.Load(FileSystem::getPath(pathMap[0]).c_str());
    two.Load(FileSystem::getPath(pathMap[1]).c_str());
    three.Load(FileSystem::getPath(pathMap[2]).c_str());

    this->Levels.push_back(one);
    this->Levels.push_back(two);
    this->Levels.push_back(three);
}

void Game::processInput(float deltaTime) {
    if (this->GameKeys[GLFW_KEY_W])
        this->camera.ProcessKeyboard(FORWARD, deltaTime);
    if (this->GameKeys[GLFW_KEY_S])
        this->camera.ProcessKeyboard(BACKWARD, deltaTime);
    if (this->GameKeys[GLFW_KEY_A])
        this->camera.ProcessKeyboard(LEFT, deltaTime);
    if (this->GameKeys[GLFW_KEY_D])
        this->camera.ProcessKeyboard(RIGHT, deltaTime);
    if(this->GameKeys[GLFW_KEY_R])
    {
        GameLevel tmp;
        tmp.Load(FileSystem::getPath(pathMap[levelID]).c_str());
        this->Levels[levelID] = tmp;
    }
}

void Game::render() {
    //Renderer->DrawSprite(ResourceManager::GetTexture("box"),glm::vec3(2.0f), glm::vec3(1.0f), 45.0f, glm::vec3(1.0f));
    if(this->Levels[this->levelID].update() && this->levelID<2)
        this->levelID++;

    this->Levels[this->levelID].Draw(*Renderer, *BoxRenderer);
}

Camera &Game::getCamera() {
    return camera;
}
