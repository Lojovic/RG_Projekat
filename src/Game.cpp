#include "Game.h"
#include "ResourceManager.h"
#include "SpriteRenderer.h"
#include "learnopengl/filesystem.h"

SpriteRenderer *Renderer;

Game::Game(unsigned int width, unsigned int height) : camera(Camera(glm::vec3(0.0f, 0.0f, 3.0f))){
    this->width = width;
    this->height = height;
}

Game::~Game() {
    delete Renderer;
}

void Game::init() {
    //load shader
    ResourceManager::LoadShader(FileSystem::getPath("resources/shaders/vertexShader.vs.glsl").c_str(),
                                FileSystem::getPath("resources/shaders/fragmentShader.fs.glsl").c_str(), nullptr, "sprite");
    //configure shader
    //only once has to be done
    ResourceManager::GetShader("sprite").Use().SetInteger("image", 0);
    //set render-specific controls
    Renderer = new SpriteRenderer(ResourceManager::GetShader("sprite"), this->camera);

    //load texture
    ResourceManager::LoadTexture(FileSystem::getPath("resources/textures/container.jpg").c_str(), false, "box");
    ResourceManager::LoadTexture(FileSystem::getPath("resources/textures/awesomeface.png").c_str(), true, "folk");
    ResourceManager::LoadTexture(FileSystem::getPath("resources/textures/brickwall.jpg").c_str(), false, "wall");
    ResourceManager::LoadTexture(FileSystem::getPath("resources/textures/floor.png").c_str(), false, "floor");
    GameLevel one;
    one.Load(FileSystem::getPath("resources/levels/1.txt").c_str());

    this->Levels.push_back(one);
}

void Game::processInput(float deltaTime) {
    if(this->GameKeys[GLFW_KEY_W])
        this->camera.ProcessKeyboard(FORWARD, deltaTime);
    if(this->GameKeys[GLFW_KEY_S])
        this->camera.ProcessKeyboard(BACKWARD, deltaTime);
    if(this->GameKeys[GLFW_KEY_A])
        this->camera.ProcessKeyboard(LEFT, deltaTime);
    if(this->GameKeys[GLFW_KEY_D])
        this->camera.ProcessKeyboard(RIGHT, deltaTime);
}

void Game::update(float deltaTime) {

}

void Game::render() {
    //Renderer->DrawSprite(ResourceManager::GetTexture("box"),glm::vec3(2.0f), glm::vec3(1.0f), 45.0f, glm::vec3(1.0f));
    this->Levels[0].Draw(*Renderer);
}

Camera &Game::getCamera() {
    return camera;
}
