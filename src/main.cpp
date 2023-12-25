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

GLfloat point[]{
  0.0f,  50.0f, 0.0f,
  50.0f, -50.0f, 0.0f,
  -50.0f, -50.0f, 0.0f
};

GLfloat colors[]{
  1.0f, 0.0f, 0.0f,
  0.0f, 1.0f, 0.0f,
  0.0f, 0.0f, 1.0f
};

GLfloat texCoord[]{
  0.5f, 1.5f,
  1.0f, 0.0f,
  0.0f, 0.0f
};

using namespace std;

bool isEagle = false;

glm::ivec2 g_windowSize(640, 480);

void glfwWindowSizeCallback(GLFWwindow *win, int width, int height) {
  g_windowSize.x = width;
  g_windowSize.y = height;
  glViewport(0, 0, width, height);
}

void glfwKeyCallback(GLFWwindow *win, int key, int scan, int act, int mode) {
  if(key == GLFW_KEY_ESCAPE && act == GLFW_PRESS) {
    glfwSetWindowShouldClose(win, GL_TRUE);
  }
  if(key == GLFW_KEY_ENTER && act == GLFW_PRESS) {
    isEagle = !isEagle;
  }

}

int main(int argc, char *argv[]) {
  // Initialize the library
  if(!glfwInit()) {
    cout << "glfwInit failed" << endl;
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

  cout << "Render: " << glGetString(GL_RENDERER) << endl;
  cout << "OpenGL version: " << glGetString(GL_VERSION) << endl;

  glClearColor(1.0, 1.0, 0, 1);
  {
    ResourceManager resourceManager(argv[0]);
    const char *defaultShaderProgramName = "DefaultShader";
    auto pDefaultShaderProgram = resourceManager.loadShader(defaultShaderProgramName, "res/shaders/vertex.glsl",
      "res/shaders/fragment.glsl");
    if(!pDefaultShaderProgram) {
      std::cerr << "Can't create the default shader program: " << defaultShaderProgramName << std::endl;
      return -1;
    }

    const char *spriteShaderProgramName = "SpriteShader";
    auto pSpriteShaderProgram = resourceManager.loadShader(spriteShaderProgramName, "res/shaders/vSprite.glsl",
      "res/shaders/fSprite.glsl");
    if(!pSpriteShaderProgram) {
      std::cerr << "Can't create the sprite shader program: " << spriteShaderProgramName << std::endl;
      return -1;
    }

    auto tex = resourceManager.loadTexture("DefaultTexture", "res/textures/map_16x16.png");
    
    vector<string> subTextureNames{
      "block",
      "topBlock",
      "bottomBlock",
      "leftBlock",
      "rightBlock",
      "topLeftBlock",
      "bottomLeftBlock",
      "topRightBlock",
      "bottomRightBlock",
      "concrete",
      "topConcrete",
      "bottomConcrete",
      "leftConcrete",
      "rightConcrete",
      "leftTotConcrete",
      "rightTopConcrete",
      "bottomLeftConcrete",
      "bottomRightConcrete",
      "water1",
      "water2",
      "water3",
      "trees",
      "ice",
      "wall",
      "eagle",
      "deadEagle",
      "nothing",
      "respawn1"
      "respawn2"
      "respawn3"
      "respawn4"
    };

    auto pTextureAtlas = resourceManager.loadTextureAtlas("DefaultTextureAtlas", "res/textures/map_16x16.png",
      subTextureNames, 16, 16);

    auto pSprite = resourceManager.loadSprite("NewSprite", "DefaultTextureAtlas", spriteShaderProgramName,
      100, 100, "concrete");
    pSprite->setPosition(glm::vec2(120, 250));

    auto pAnimatedSprite = resourceManager.loadAnimatedSprite("newAnimetedSprite", "DefaultTextureAtlas", spriteShaderProgramName,
      100, 100, "concrete");
    pAnimatedSprite->setPosition(glm::vec2(300, 300));

    vector<pair<string, uint64_t>> waterState{{"water1", 1000000000}, {"water2", 1000000000},
      {"water3", 1000000000}};
    /*waterState.emplace_back(make_pair("water1", 1000000000));
    waterState.emplace_back(make_pair("water2", 1000000000));
    waterState.emplace_back(make_pair("water3", 1000000000));*/

    vector<pair<string, uint64_t>> eagleState;
    eagleState.emplace_back(make_pair("eagle", 1000000000));
    eagleState.emplace_back(make_pair("deadEagle", 1000000000));

    pAnimatedSprite->insertState("waterState", waterState);
    pAnimatedSprite->insertState("eaglState", eagleState);

    pAnimatedSprite->setState("waterState");

    GLuint points_vbo = 0;
    glGenBuffers(1, &points_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, points_vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(point), point, GL_STATIC_DRAW);

    GLuint colors_vbo = 0;
    glGenBuffers(1, &colors_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, colors_vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW);

    GLuint texCoord_vbo = 0;
    glGenBuffers(1, &texCoord_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, texCoord_vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(texCoord), texCoord, GL_STATIC_DRAW);

    GLuint vao = 0;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, points_vbo);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, colors_vbo);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

    glEnableVertexAttribArray(2);
    glBindBuffer(GL_ARRAY_BUFFER, texCoord_vbo);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, nullptr);

    pDefaultShaderProgram->use();
    pDefaultShaderProgram->setInt("tex", 0);

    glm::mat4 modelMatrix_1(1.f);
    modelMatrix_1 = glm::translate(modelMatrix_1, glm::vec3(100.f, 51.f, 0.f));

    glm::mat4 modelMatrix_2(1.f);
    modelMatrix_2 = glm::translate(modelMatrix_2, glm::vec3(589.f, 51.f, 0.f));

    glm::mat4 projectMatrix = glm::ortho(0.f, static_cast<float>(g_windowSize.x), 0.f, 
      static_cast<float>(g_windowSize.y), -100.0f, 100.0f);

    pDefaultShaderProgram->setMatrix4("projectionMat", projectMatrix);

    pSpriteShaderProgram->use();
    pSpriteShaderProgram->setInt("tex", 0);
    pSpriteShaderProgram->setMatrix4("projectionMat", projectMatrix);

    auto lastTime = chrono::high_resolution_clock::now();

    // Loop until the user closes the window
    while(!glfwWindowShouldClose(win)) {

      if(isEagle && pAnimatedSprite->getState() != "eaglState") {
        pAnimatedSprite->setState("eaglState");
      } else if(!isEagle && pAnimatedSprite->getState() != "waterState") {
        pAnimatedSprite->setState("waterState");
      }

      auto currentTime = chrono::high_resolution_clock::now();
      uint64_t duration = chrono::duration_cast<chrono::nanoseconds>(currentTime - lastTime).count();
      lastTime = currentTime;
      pAnimatedSprite->update(duration);

      // Render here
      glClear(GL_COLOR_BUFFER_BIT);

      pDefaultShaderProgram->use();
      glBindVertexArray(vao);
      tex->bind();

      pDefaultShaderProgram->setMatrix4("modelMat", modelMatrix_1);
      glDrawArrays(GL_TRIANGLES, 0, 3);

      pDefaultShaderProgram->setMatrix4("modelMat", modelMatrix_2);
      glDrawArrays(GL_TRIANGLES, 0, 3);

      pSprite->render();

      pAnimatedSprite->render();

      // Swap front and back buffers
      glfwSwapBuffers(win);

      // Poll for and process events
      glfwPollEvents();
    }
    glDeleteBuffers(1, &points_vbo);
    glDeleteBuffers(1, &colors_vbo);
    glDeleteBuffers(1, &texCoord_vbo);
    glDeleteVertexArrays(1, &vao);
  }

  glfwTerminate();

  return 0;
}