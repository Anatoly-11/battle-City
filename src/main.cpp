#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
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

  // Make the window's context current
  glfwMakeContextCurrent(win);

  if(!gladLoadGL()) {
    cout << "Can't load GLAD!" << endl;
    return -1;
  }

  cout << "Render: " << glGetString(GL_RENDERER) << endl;
  cout << "OpenGL version: " << glGetString(GL_VERSION) << endl;

  glClearColor(1, 1, 0, 1);

  glfwSetWindowSizeCallback(win, glfwWindowSizeCallback);
  glfwSetKeyCallback(win, glfwKeyCallback);

  // Loop until the user closes the window
  while(!glfwWindowShouldClose(win)) {
    // Render here
    glClear(GL_COLOR_BUFFER_BIT);

    // Swap front and back buffers
    glfwSwapBuffers(win);

    // Poll for and process events
    glfwPollEvents();
  }
  glfwTerminate();

  return 0;
}