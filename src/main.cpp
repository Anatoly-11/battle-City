#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/vec2.hpp>

#include <iostream>
#include <chrono>

#include "Resources/ResourceManager.h"
#include "Physics/PhysicsEngine.h"

#include "Game/Game.h"
#include "Renderer/Renderer.h"

static constexpr unsigned int SCALE = 3;
static constexpr unsigned int BLOCK_SIZE = 16;

glm::uvec2 g_windowSize(SCALE * 16 * BLOCK_SIZE, SCALE * 15 * BLOCK_SIZE);

std::unique_ptr<Game> g_game = std::make_unique<Game>(g_windowSize);


void glfwWindowSizeCallback(GLFWwindow *pWin, int width, int height) {
	g_windowSize.x = width;
	g_windowSize.y = height;
	g_game->setWindowSize(g_windowSize);
}

void glfwKeyCallback(GLFWwindow *pWin, int key, int scan, int act, int mode) {
	if(act == GLFW_PRESS) {
		if(key != GLFW_KEY_ESCAPE) {
			g_game->setKey(key, mode);
		} else {
			glfwSetWindowShouldClose(pWin, GL_TRUE);
		}
	}
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
	GLFWwindow *pWindow = glfwCreateWindow(g_windowSize.x, g_windowSize.y, "Battle-Ciyt", nullptr, nullptr);
	if(!pWindow) {
		std::cout << "glfwCreateWindow failed" << std::endl;
		glfwTerminate();
		return -1;
	}

	glfwSetWindowSizeCallback(pWindow, glfwWindowSizeCallback);
	glfwSetKeyCallback(pWindow, glfwKeyCallback);
	//glfwSetInputMode(pWindow, GLFW_STICKY_KEYS, GLFW_TRUE);

	// Make the window's context current
	glfwMakeContextCurrent(pWindow);

	if(!gladLoadGL()) {
		std::cout << "Can't load GLAD!" << std::endl;
		return -1;
	}

	std::cout << RenderEngine::Renderer::getInfo() << std::endl;

	ResourceManager::setExecutablePath(argv[0]);

	Physics::PhysicsEngine::init();

	g_game->init();

	//constexpr float coef_scale = 3.f;
	//glfwSetWindowSize(pWindow, static_cast<int>(coef_scale*g_game->getCurrentWidth()),
	//  static_cast<int>(coef_scale*g_game->getCurrentHeight()));


	RenderEngine::Renderer::setClearColor(0.f, 0.f, 0.f, 1.f);

	RenderEngine::Renderer::setDepthTest(true);
	auto prevTime = std::chrono::high_resolution_clock::now();
	// Loop until the user closes the window
	while(!glfwWindowShouldClose(pWindow)) {

		auto currentTime = std::chrono::high_resolution_clock::now();
		double dutation = std::chrono::duration<double, std::milli>(currentTime  - prevTime).count();
		prevTime = currentTime;

		glfwPollEvents();

		g_game->update(dutation);
		Physics::PhysicsEngine::update(dutation);
		
		RenderEngine::Renderer::clear();
		g_game->render();

		glfwSwapBuffers(pWindow);
	}
	Physics::PhysicsEngine::terminate();
	g_game = nullptr;
	ResourceManager::unloadAllResources();

	glfwTerminate();

	return 0;
}