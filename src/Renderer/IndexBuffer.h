#ifndef _INDEXBUFFER_H
#define _INDEXBUFFER_H 1.0

#include <glad/glad.h>

namespace Renderer {
  class IndexBuffer {
    IndexBuffer(const IndexBuffer&) = delete;
    IndexBuffer &operator=(const IndexBuffer&) = delete;
  public:
    IndexBuffer() noexcept;

    IndexBuffer(IndexBuffer &&indexBuffer) noexcept;

    IndexBuffer &operator=(IndexBuffer &&indexBuffer) noexcept;

    ~IndexBuffer() noexcept;

    void init(const void *data, const unsigned int size) noexcept;

    void bind() const noexcept;

    void unbind() const noexcept;

  private:
    GLuint m_id;
  };
}
#endif // !_INDEXBUFFER_H