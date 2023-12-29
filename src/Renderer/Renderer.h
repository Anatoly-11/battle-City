#ifndef _RENDERER_H
#define _RENDERER_H 1.0

#include <string>

namespace RendererEngine {
  class VertexArray;
  class IndexBuffer;
  class ShaderProgram;
  class Renderer {
  public:
    static void draw(const VertexArray &vertexArray, const IndexBuffer &indexBuffer,
      const ShaderProgram &shader) noexcept;
    static void setClearColor(const float r, const float g, const float b, const float a) noexcept;
    static void clear() noexcept;
    static void setViewport(const unsigned int width, const unsigned int height,
      const unsigned int leftOffset = 0, const unsigned int bottomOffset = 0) noexcept;
    static const std::string getRendererStr() noexcept;
    static const std::string getVersionStr() noexcept;
    static const std::string getInfo() noexcept;
  };
}
#endif // !_RENDERER_H