#include "VertexArray.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"

namespace RendererEngine {
  VertexArray::VertexArray() noexcept : m_id(0), m_elementsCount(0) {
    glGenVertexArrays(1, &m_id);
  }

  VertexArray::VertexArray(VertexArray &&VertexArray) noexcept {
    m_id = VertexArray.m_id;
    VertexArray.m_id = 0;
  }

  VertexArray &VertexArray::operator=(VertexArray &&VertexArray) noexcept {
    m_id = VertexArray.m_id;
    VertexArray.m_id = 0;
    return *this;
  }

  VertexArray::~VertexArray() noexcept {
    glDeleteVertexArrays(1, &m_id);
  }

  void VertexArray::bind() const noexcept {
    glBindVertexArray(m_id);
  }

  void VertexArray::unbind() const noexcept {
    glBindVertexArray(0);
  }

  void VertexArray::addBuffer(const VertexBuffer &vertexBuffer, const VertexBufferLayout &layout) noexcept {
    bind();
    vertexBuffer.bind();
    const auto& layoutElemenys = layout.getLayoutElements();
    GLbyte *offset = nullptr;
    for(unsigned int i = 0; i < layoutElemenys.size(); ++i) {
      const auto &currentLayoutElement = layoutElemenys[i];
      GLuint currentAttribIndex = m_elementsCount + i;
      glEnableVertexAttribArray(currentAttribIndex);
      glVertexAttribPointer(currentAttribIndex, currentLayoutElement.count, currentLayoutElement.type,
        currentLayoutElement.normalized, layout.getStride(), offset);
      offset += currentLayoutElement.size;
    }
    m_elementsCount += static_cast<unsigned int>(layoutElemenys.size());
  }
}