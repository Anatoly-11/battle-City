#pragma once

#include <glad/glad.h>

namespace RenderEngine {

  class VertexBuffer;
  class VertexBufferLayout;

  class VertexArray {
    VertexArray(const VertexArray&) = delete;
    VertexArray &operator=(const VertexArray&) = delete;
  public:
    VertexArray() noexcept;

    VertexArray(VertexArray &&VertexArray) noexcept;

    VertexArray &operator=(VertexArray &&VertexArray) noexcept;

    ~VertexArray() noexcept;

    void bind() const noexcept;

    void unbind() const noexcept;

    void addBuffer(const VertexBuffer &vertexBuffer, const VertexBufferLayout &layout) noexcept;

  private:
    GLuint m_id;
    unsigned int m_elementsCount;
  };
}