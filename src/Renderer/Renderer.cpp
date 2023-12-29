#include "Renderer.h"

#include "VertexArray.h"
#include "IndexBuffer.h"
#include "ShaderProgram.h"
#include <format>

namespace RendererEngine {
  void Renderer::draw(const VertexArray &vertexArray, const IndexBuffer &indexBuffer,
    const ShaderProgram &shader) noexcept {
    shader.use();
    vertexArray.bind();
    indexBuffer.bind();
    glDrawElements(GL_TRIANGLES, indexBuffer.getCount(), GL_UNSIGNED_INT, nullptr);
  }

  void Renderer::setClearColor(const float r, const float g, const float b, const float a) noexcept {
    glClearColor(r, g, b, a);
  }

  void Renderer::clear() noexcept {
    glClear(GL_COLOR_BUFFER_BIT);
  }

  void Renderer::setViewport(const unsigned int width, const unsigned int height, const unsigned int leftOffset,
    const unsigned int bottomOffset) noexcept {
    glViewport(leftOffset, bottomOffset, width, height);
  }

  const std::string Renderer::getRendererStr() noexcept {
    return (char*)glGetString(GL_RENDERER);
  }

  const std::string Renderer::getVersionStr() noexcept {
    return (char*)glGetString(GL_VERSION);
  }

  const std::string Renderer::getInfo() noexcept {
    return std::format("Render: {}\nOpenGL version: {}", (char*)glGetString(GL_RENDERER),
      (char*)glGetString(GL_VERSION));
  }
}