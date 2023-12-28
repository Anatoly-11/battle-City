#ifndef _VERTEXBUFFER_H
#define _VERTEXBUFFER_H 1.0

#include <glad/glad.h>

namespace Renderer {
  class VertexBuffer {
    VertexBuffer(const VertexBuffer&) = delete;
    VertexBuffer &operator=(const VertexBuffer&) = delete;
  public:
    VertexBuffer() noexcept;

    VertexBuffer(VertexBuffer &&vertexBuffer) noexcept;

    VertexBuffer &operator=(VertexBuffer &&vertexBuffer) noexcept;

    ~VertexBuffer() noexcept;

    void init(const void *data, const unsigned int size) noexcept;

    void update(const void *data, const unsigned int size) noexcept;

    void bind() const noexcept;

    void unbind() const noexcept;

  private:
    GLuint m_id;
  };
}
#endif // !_VERTEXBUFFER_H