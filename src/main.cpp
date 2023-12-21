#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "Renderer/ShaderProgram.h"
#include "Resources/ResourceManager.h"
#include "Renderer/Texture2D.h"
//-------------------------------------------------------------------------------------------------------------
GLfloat point[]{
  0.0f,  0.5f, 0.0f,
  0.5f, -0.5f, 0.0f,
  -0.5f, -0.5f, 0.0f
};
//-------------------------------------------------------------------------------------------------------------
GLfloat colors[]{
  1.0f, 0.0f, 0.0f,
  0.0f, 1.0f, 0.0f,
  0.0f, 0.0f, 1.0f
};
//-------------------------------------------------------------------------------------------------------------
GLfloat texCoord[]{
  0.5f, 1.5f,
  1.0f, 0.0f,
  0.0f, 0.0f
};
//-------------------------------------------------------------------------------------------------------------
using namespace std;
//-------------------------------------------------------------------------------------------------------------
int g_windowSizeX = 640;
int g_windowSizeY = 480;
//-------------------------------------------------------------------------------------------------------------
void glfwWindowSizeCallback(GLFWwindow *win, int width, int height) {
  g_windowSizeX = width;
  g_windowSizeY = height;
  glViewport(0, 0, width, height);
}
//-------------------------------------------------------------------------------------------------------------
void glfwKeyCallback(GLFWwindow *win, int key, int scan, int act, int mode) {
  if(key == GLFW_KEY_ESCAPE && act == GLFW_PRESS) {
    glfwSetWindowShouldClose(win, GL_TRUE);
  }
}
//-------------------------------------------------------------------------------------------------------------
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
  GLFWwindow *win = glfwCreateWindow(g_windowSizeX, g_windowSizeY, "Battle-Ciyt", nullptr, nullptr);
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
    const char *shaderProgramName = "DefaultShader";
    auto pDefaultShaderProgram = resourceManager.loadShaders(shaderProgramName, "res/shaders/vertex.glsl",
      "res/shaders/fragment.glsl");
    if(!pDefaultShaderProgram) {
      std::cerr << "Can't create shader program: " << shaderProgramName << std::endl;
      return -1;
    }
    auto tex = resourceManager.loadTexture("defaultTexture", "res/textures/map_16x16.png");
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

    glEnableVertexAttribArray(2); //texCoord
    glBindBuffer(GL_ARRAY_BUFFER, texCoord_vbo);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, nullptr);

    pDefaultShaderProgram->use();
    pDefaultShaderProgram->setInt("tex", 0);

    // Loop until the user closes the window
    while(!glfwWindowShouldClose(win)) {
      // Render here
      glClear(GL_COLOR_BUFFER_BIT);

      pDefaultShaderProgram->use();
      glBindVertexArray(vao);
      tex->bind();
      glDrawArrays(GL_TRIANGLES, 0, 3);


      // Swap front and back buffers
      glfwSwapBuffers(win);

      // Poll for and process events
      glfwPollEvents();
    }
  }
  glfwTerminate();

  return 0;
}