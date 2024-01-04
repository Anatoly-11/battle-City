#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/vec2.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <iostream>
#include <chrono>

#include "Resources/ResourceManager.h"
#include "Game/Game.h"
#include "Renderer/Renderer.h"

using namespace std;

glm::ivec2 g_windowSize(13 * 16, 14 * 16);

unique_ptr<Game> g_game = make_unique<Game>(g_windowSize);


void glfwWindowSizeCallback(GLFWwindow *win, int width, int height) {
  g_windowSize.x = width;
  g_windowSize.y = height;

  const float map_aspect_ratio = static_cast<float>(g_game->getCurrentLevelWidth()) / g_game->getCurrentLevelHeight();
  unsigned int viewPortWidth = g_windowSize.x;
  unsigned int viewPortHeight = g_windowSize.y;
  unsigned int viewPortLeftOffset = 0;
  unsigned int viewPortBottomOffset = 0;
  if((float)g_windowSize.x / g_windowSize.y > map_aspect_ratio) {
    viewPortWidth = static_cast<unsigned int>((float)g_windowSize.y * map_aspect_ratio);
    viewPortLeftOffset = static_cast<unsigned int>(((float)g_windowSize.x - viewPortWidth) / 2.f);
  } else if((float)g_windowSize.x / g_windowSize.y < map_aspect_ratio) {
    viewPortHeight = static_cast<unsigned int>(((float)g_windowSize.x / map_aspect_ratio));
    viewPortBottomOffset = static_cast<unsigned int>(((float)g_windowSize.y - viewPortHeight) / 2.f);
  }
  RendererEngine::Renderer::setViewport(viewPortWidth, viewPortHeight, viewPortLeftOffset, viewPortBottomOffset);
}

void glfwKeyCallback(GLFWwindow *win, int key, int scan, int act, int mode) {
  if(key == GLFW_KEY_ESCAPE && act == GLFW_PRESS) {
    glfwSetWindowShouldClose(win, GL_TRUE);
  }
  g_game->setKey(key, act);
}

int main(int argc, char *argv[]) {
  // Initialize the library
  if(!glfwInit()) {
    std::cout << "glfwInit failed" << std::endl;
    return -1;
  }

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  // Create a windowed mode window and its OpenGL context
  GLFWwindow *win = glfwCreateWindow(g_windowSize.x, g_windowSize.y, "Battle-Ciyt", nullptr, nullptr);
  if(!win) {
    cout << "glfwCreateWindow failed" << endl;
    glfwTerminate();
    return -1;
  }

  glfwSetWindowSizeCallback(win, glfwWindowSizeCallback);
  glfwSetKeyCallback(win, glfwKeyCallback);

  // Make the window's context current
  glfwMakeContextCurrent(win);

  if(!gladLoadGL()) {
    cout << "Can't load GLAD!" << endl;
    return -1;
  }

  cout << RendererEngine::Renderer::getInfo() << endl;

  ResourceManager::setExecutablePath(argv[0]);
  
  g_game->init();

  constexpr float coef_scale = 3.5;

  glfwSetWindowSize(win, static_cast<int>(coef_scale*g_game->getCurrentLevelWidth()),
    static_cast<int>(coef_scale*g_game->getCurrentLevelHeight()));

  auto lastTime = chrono::high_resolution_clock::now();

  RendererEngine::Renderer::setClearColor(0.f, 0.f, 0.f, 1.f);

  RendererEngine::Renderer::setDepthTest(true);

  // Loop until the user closes the window
  while(!glfwWindowShouldClose(win)) {
    // Poll for and process events
    glfwPollEvents();

    auto currentTime = chrono::high_resolution_clock::now();
    double duration = chrono::duration<double, std::milli>(currentTime - lastTime).count();
    lastTime = currentTime;
    g_game->update(duration);

    // Render here
    RendererEngine::Renderer::clear();
    g_game->render();

    // Swap front and back buffers
    glfwSwapBuffers(win);
  }
  g_game = nullptr;
  ResourceManager::unloadAllResources();

  glfwTerminate();

  return 0;
}