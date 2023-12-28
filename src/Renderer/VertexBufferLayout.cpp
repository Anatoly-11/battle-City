#include "VertexBufferLayout.h"
namespace Renderer {
  VertexBufferLayout::VertexBufferLayout() noexcept : m_stride(0) {
  }

  void VertexBufferLayout::reserveElements(size_t count) noexcept {
    m_latotuElements.reserve(count);
  }

  unsigned int VertexBufferLayout::getStride() const noexcept {
    return m_stride;
  }

  const std::vector<VertexBufferLayoutElement> &VertexBufferLayout::getLayoutElements() const noexcept {
    return m_latotuElements;
  }

  void VertexBufferLayout::adLayoutEletmtntsFloat(const unsigned int count, const bool normalized) noexcept {
    unsigned int size = count * sizeof(GLfloat);
    m_latotuElements.emplace_back(static_cast<int>(count), GL_FLOAT, normalized, size);
    m_stride += size;
  }
}