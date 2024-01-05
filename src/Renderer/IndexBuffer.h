#ifndef _INDEXBUFFER_H
#define _INDEXBUFFER_H 1.0

#include <glad/glad.h>
#include <cstdint>

namespace RendererEngine {
  class IndexBuffer {
    IndexBuffer(const IndexBuffer&) = delete;
    IndexBuffer &operator=(const IndexBuffer&) = delete;
  public:
    IndexBuffer() noexcept;

    IndexBuffer(IndexBuffer &&indexBuffer) noexcept;

    IndexBuffer &operator=(IndexBuffer &&indexBuffer) noexcept;

    ~IndexBuffer() noexcept;

    void init(const void *data, const unsigned int count) noexcept;

    void bind() const noexcept;

    void unbind() const noexcept;

    unsigned int getCount() const noexcept;

  private:
    GLuint m_id;
    unsigned int m_count;
  };
}
#endif // !_INDEXBUFFER_H