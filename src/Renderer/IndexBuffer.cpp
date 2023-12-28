#include "IndexBuffer.h"

namespace Renderer {
  IndexBuffer::IndexBuffer() noexcept : m_id(0) {
  }

  IndexBuffer::IndexBuffer(IndexBuffer &&indexBuffer) noexcept {
    m_id = indexBuffer.m_id;
    indexBuffer.m_id = 0;
  }

  IndexBuffer &IndexBuffer::operator=(IndexBuffer &&indexBuffer) noexcept {
    m_id = indexBuffer.m_id;
    indexBuffer.m_id = 0;
    return *this;
  }

  IndexBuffer::~IndexBuffer() noexcept {
    glDeleteBuffers(1, &m_id);
  }

  void IndexBuffer::init(const void *data, const unsigned int size) noexcept {
    glGenBuffers(1, &m_id);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_id);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
  }

  void IndexBuffer::bind() const noexcept {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_id);
  }

  void IndexBuffer::unbind() const noexcept {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
  }
}