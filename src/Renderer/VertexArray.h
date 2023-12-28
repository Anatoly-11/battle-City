#ifndef _VERTEXARRAY_H
#define _VERTEXARRAY_H 1.0

#include <glad/glad.h>
//#include "VertexBuffer.h"

namespace Renderer {

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
#endif // !_VERTEXARRAY_H