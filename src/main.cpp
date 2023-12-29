#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/vec2.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <iostream>
#include <chrono>

#include "Renderer/ShaderProgram.h"
#include "Resources/ResourceManager.h"
#include "Renderer/Texture2D.h"
#include "Renderer/Sprite.h"
#include "Renderer/AnimatedSprite.h"
#include "Game/Game.h"
#include "Renderer/Renderer.h"

using namespace std;

glm::ivec2 g_windowSize(640, 480);

Game g_game(g_windowSize);

void glfwWindowSizeCallback(GLFWwindow *win, int width, int height) {
  g_windowSize.x = width;
  g_windowSize.y = height;
  RendererEngine::Renderer::setViewport(width, height);
}

void glfwKeyCallback(GLFWwindow *win, int key, int scan, int act, int mode) {
  if(key == GLFW_KEY_ESCAPE && act == GLFW_PRESS) {
    glfwSetWindowShouldClose(win, GL_TRUE);
  }
  g_game.setKey(key, act);
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
  if(!g_game.init()) {
    return -1;
  }

  auto lastTime = chrono::high_resolution_clock::now();

  RendererEngine::Renderer::setClearColor(0.f, 0.f, 0.f, 1.f);

  // Loop until the user closes the window
  while(!glfwWindowShouldClose(win)) {
    // Poll for and process events
    glfwPollEvents();

    auto currentTime = chrono::high_resolution_clock::now();
    uint64_t duration = chrono::duration_cast<chrono::nanoseconds>(currentTime - lastTime).count();
    lastTime = currentTime;
    g_game.update(duration);

    // Render here
    RendererEngine::Renderer::clear();
    g_game.render();

    // Swap front and back buffers
    glfwSwapBuffers(win);
  }

  ResourceManager::unloadAllResources();

  glfwTerminate();

  return 0;
}