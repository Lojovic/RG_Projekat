#include "Game.h"

#include <iostream>

void
framebuffer_size_callback(GLFWwindow *window, int width, int height);
void
mouse_callback(GLFWwindow *window, double xpos, double ypos);
void
scroll_callback(GLFWwindow *window, double xoffset, double yoffset);
void
key_callback(GLFWwindow *window, int key, int scancode, int action, int mode);

// screen dimensions
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

// mouse coordinates
float lastX = 1.0f * SCR_WIDTH / 2.0f;
float lastY = 1.0f * SCR_HEIGHT / 2.0f;
bool firstMouse = true;

// timing
float deltaTime = 0.0f; // time between current frame and last frame
float lastFrame = 0.0f;

// Create Sokoban object
Game Sokoban(SCR_WIDTH, SCR_HEIGHT);

auto
main() -> int
{
  // glfw: initialize and configure
  // ------------------------------
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

  // glfw window creation
  GLFWwindow *window =
      glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Sokoban3D", nullptr, nullptr);
  if (window == nullptr) {
    std::cout << "Failed to create GLFW window" << std::endl;
    glfwTerminate();
    return -1;
  }

  glfwMakeContextCurrent(window);
  glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
  glfwSetCursorPosCallback(window, mouse_callback);
  glfwSetScrollCallback(window, scroll_callback);
  glfwSetKeyCallback(window, key_callback);

  glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

  // glad: load all OpenGL function pointers
  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    std::cout << "Failed to initialize GLAD" << std::endl;
    return -1;
  }

  // activating blending
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  // initialize game assets
  Sokoban.init();

  // render loop
  while (!glfwWindowShouldClose(window)) {
    float currentFrame = glfwGetTime();
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;
    // input
    glfwPollEvents();

    // process input
    Sokoban.processInput(deltaTime);

    // render
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    Sokoban.render();

    // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved
    // etc.)
    glfwSwapBuffers(window);
  }

  // de-allocate all resources once they've outlived their purpose:
  ResourceManager::Clear();

  // glfw: terminate, clearing all previously allocated GLFW resources.
  glfwTerminate();
  return 0;
}

// process all input
void
key_callback(GLFWwindow *window, int key, int scancode, int action, int mode)
{
  if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    glfwSetWindowShouldClose(window, true);

  // when a movement key is pressed we render the level again
  if (key == GLFW_KEY_UP && action == GLFW_RELEASE) {
    if (Sokoban.Levels[Sokoban.levelID].move(GLFW_KEY_UP))
      Sokoban.render();
  }
  if (key == GLFW_KEY_DOWN && action == GLFW_PRESS) {
    if (Sokoban.Levels[Sokoban.levelID].move(GLFW_KEY_DOWN))
      Sokoban.render();
  }
  if (key == GLFW_KEY_LEFT && action == GLFW_PRESS) {
    if (Sokoban.Levels[Sokoban.levelID].move(GLFW_KEY_LEFT))
      Sokoban.render();
  }
  if (key == GLFW_KEY_RIGHT && action == GLFW_PRESS) {
    if (Sokoban.Levels[Sokoban.levelID].move(GLFW_KEY_RIGHT))
      Sokoban.render();
  }

  // camera locking
  if (key == GLFW_KEY_L && action == GLFW_PRESS) {
    Sokoban.cameraLock = !Sokoban.cameraLock;
  }

  if (key >= 0 && key < 1024) {
    if (action == GLFW_PRESS)
      Sokoban.GameKeys[key] = true;
    else if (action == GLFW_RELEASE)
      Sokoban.GameKeys[key] = false;
  }
}

void
scroll_callback(GLFWwindow *window, double xoffset, double yoffset)
{
  Sokoban.getCamera().ProcessMouseScroll(yoffset);
}

void
mouse_callback(GLFWwindow *window, double xpos, double ypos)
{
  if (firstMouse) {
    lastX = xpos;
    lastY = ypos;
    firstMouse = false;
  }

  float xoffset = xpos - lastX;
  float yoffset =
      lastY - ypos; // reversed since y-coordinates go from bottom to top

  lastX = xpos;
  lastY = ypos;

  Sokoban.getCamera().ProcessMouseMovement(xoffset, yoffset);
}

// glfw: whenever the window size changed (by OS or user resize) this callback
// function executes
void
framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
  // make sure the viewport matches the new window dimensions; note that width
  // and height will be significantly larger than specified on retina displays.
  glViewport(0, 0, width, height);
}
