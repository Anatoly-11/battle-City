#ifndef _VERTEXBUFFERLAYOUT_H
#define _VERTEXBUFFERLAYOUT_H 1.0

#include <vector>
#include <glad/glad.h>

namespace RenderEngine {
  struct VertexBufferLayoutElement {
    GLint count;
    GLenum type;
    GLboolean normalized;
    unsigned int size;
  };

  class VertexBufferLayout {
  public:
    VertexBufferLayout() noexcept;

    //~VertexBufferLayout() noexcept;

    void reserveElements(size_t count) noexcept;

    unsigned int getStride() const noexcept;

    const std::vector<VertexBufferLayoutElement> &getLayoutElements() const noexcept;

    void adLayoutEletmtntsFloat(const unsigned int count, const bool normalized) noexcept;

  private:
    std::vector<VertexBufferLayoutElement> m_latotuElements;
    unsigned int m_stride;
  };
}

#endif // !_VERTEXBUFFERLAYOUT_H