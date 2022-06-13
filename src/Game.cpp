#include "Game.h"

SpriteRenderer *Renderer;
SpriteRendererBox *BoxRenderer;
ModelRendererTorch *TorchRenderer;
SpriteRendererSkyBox *SkyBoxRenderer;

Game::Game(unsigned int width, unsigned int height) : levelID(0)
{
  this->width = width;
  this->height = height;
  this->camera.Position = glm::vec3(3.0f, 12.0f, -8.0f);
  this->pathMap[0] = "resources/levels/1.txt";
  this->pathMap[1] = "resources/levels/2.txt";
  this->pathMap[2] = "resources/levels/3.txt";
}

Game::~Game()
{
  delete Renderer;
  delete BoxRenderer;
}

void
Game::init()
{
  // load shaders
  ResourceManager::LoadShader(
      FileSystem::getPath("resources/shaders/vertexShader.vs.glsl").c_str(),
      FileSystem::getPath("resources/shaders/fragmentShader.fs.glsl").c_str(),
      nullptr, "sprite");
  ResourceManager::LoadShader(
      FileSystem::getPath("resources/shaders/vertexShader.vs.glsl").c_str(),
      FileSystem::getPath("resources/shaders/fragmentShaderBox.fs.glsl")
          .c_str(),
      nullptr, "sprite_box");

  ResourceManager::LoadShader(
      FileSystem::getPath("resources/shaders/vertexShaderTorch.vs.glsl")
          .c_str(),
      FileSystem::getPath("resources/shaders/fragmentShaderTorch.fs.glsl")
          .c_str(),
      nullptr, "model_torch");

  ResourceManager::LoadShader(
      FileSystem::getPath("resources/shaders/vertexShaderSkyBox.vs.glsl")
          .c_str(),
      FileSystem::getPath("resources/shaders/fragmentShaderSkyBox.fs.glsl")
          .c_str(),
      nullptr, "skybox");


  // configure shaders
  // only has to be done once
  ResourceManager::GetShader("sprite").Use().SetInteger("material.diffuse", 0);
  ResourceManager::GetShader("sprite").Use().SetVector3f("material.specular",
                                                         glm::vec3(0.2f));

  ResourceManager::GetShader("sprite_box")
      .Use()
      .SetInteger("material.diffuse", 0);
  ResourceManager::GetShader("sprite_box")
      .Use()
      .SetInteger("material.specular", 1);

  ResourceManager::GetShader("skybox").Use().SetInteger("skybox", 0);

  // create render objects
  Renderer =
      new SpriteRenderer(ResourceManager::GetShader("sprite"), this->camera);
  BoxRenderer = new SpriteRendererBox(ResourceManager::GetShader("sprite_box"),
                                      this->camera);
  TorchRenderer = new ModelRendererTorch(
      ResourceManager::GetShader("model_torch"), this->camera);
  SkyBoxRenderer = new SpriteRendererSkyBox(
      ResourceManager::GetShader("skybox"), this->camera);

  // load textures
  ResourceManager::LoadTexture(
      FileSystem::getPath("resources/textures/container.png").c_str(), true,
      "box");
  ResourceManager::LoadTexture(
      FileSystem::getPath("resources/textures/awesomeface.png").c_str(), true,
      "folk");
  ResourceManager::LoadTexture(
      FileSystem::getPath("resources/textures/bricks.jpg").c_str(), false,
      "wall");
  ResourceManager::LoadTexture(
      FileSystem::getPath("resources/textures/floor.png").c_str(), false,
      "floor");
  ResourceManager::LoadTexture(
      FileSystem::getPath("resources/textures/target.jpg").c_str(), false,
      "target");
  ResourceManager::LoadTexture(
      FileSystem::getPath("resources/textures/container_specular.png").c_str(),
      true, "box_specular");
  ResourceManager::LoadModel(
      FileSystem::getPath("resources/objects/torch/Torch.obj"), "torch");

  // +X (right)
  // -X (left)
  // +Y (top)
  // -Y (bottom)
  // +Z (front)
  // -Z (back)

  vector<std::string> faces{
      FileSystem::getPath("resources/textures/skybox/Lycksele/posx.jpg"),
      FileSystem::getPath("resources/textures/skybox/Lycksele/negx.jpg"),
      FileSystem::getPath("resources/textures/skybox/Lycksele/posy.jpg"),
      FileSystem::getPath("resources/textures/skybox/Lycksele/negy.jpg"),
      FileSystem::getPath("resources/textures/skybox/Lycksele/posz.jpg"),
      FileSystem::getPath("resources/textures/skybox/Lycksele/negz.jpg"),
  };

  // load cubemap
  unsigned int skyBoxID = ResourceManager::loadCubemap(faces);
  SkyBoxRenderer->setCubeMapTextureId(skyBoxID);

  // load and save levels
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

// allowing the camera to move and a level restarting feature
void
Game::processInput(float deltaTime)
{
  if (!this->cameraLock) {
    if (this->GameKeys[GLFW_KEY_W])
      this->camera.ProcessKeyboard(FORWARD, deltaTime);
    if (this->GameKeys[GLFW_KEY_S])
      this->camera.ProcessKeyboard(BACKWARD, deltaTime);
    if (this->GameKeys[GLFW_KEY_A])
      this->camera.ProcessKeyboard(LEFT, deltaTime);
    if (this->GameKeys[GLFW_KEY_D])
      this->camera.ProcessKeyboard(RIGHT, deltaTime);
  }
  if (this->GameKeys[GLFW_KEY_R]) {
    GameLevel tmp;
    tmp.Load(FileSystem::getPath(pathMap[levelID]).c_str());
    this->Levels[levelID] = tmp;
  }
}

// rendering of the current level, the light objects and the skybox
void
Game::render()
{
  if (this->Levels[this->levelID].update() && this->levelID < 2)
    this->levelID++;

  this->Levels[this->levelID].Draw(*Renderer, *BoxRenderer);
  for (glm::vec3 lightPos : this->Levels[this->levelID].Lights)
    TorchRenderer->Draw(ResourceManager::GetModel("torch"), lightPos,
                        glm::vec3(0.5f), glm::vec3(0.0f, 1.0f, 0.0f), 90.0f);
  SkyBoxRenderer->Draw();
}

auto
Game::getCamera() -> Camera &
{
  return camera;
}
