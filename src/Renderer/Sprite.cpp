#include "Sprite.h"
#include "ShaderProgram.h"
#include "Texture2D.h"
#include "VertexBufferLayout.h"
#include "Renderer.h"

#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace RendererEngine {

  Sprite::Sprite(const std::shared_ptr<Texture2D> &pTexture,
    const std::string &initialSubTexture,
    const std::shared_ptr<ShaderProgram> &pShaderProgram) noexcept : m_pTexture(pTexture),
    m_pShaderProgram(pShaderProgram), lastFrameId(0)
  {
    const GLfloat vertexCoords[]{
      // 1--2
      // |  |
      // 0--3

      // X  Y

      0.f, 0.f,
      0.f, 1.f,
      1.f, 1.f,
      1.f, 0.f,
    };

    auto subTexture = m_pTexture->getSubTexture(initialSubTexture);

    const GLfloat textureCoords[]{
      // U  V
      subTexture.leftBottomUV.x, subTexture.leftBottomUV.y,
      subTexture.leftBottomUV.x, subTexture.rightTopUV.y,
      subTexture.rightTopUV.x, subTexture.rightTopUV.y,
      subTexture.rightTopUV.x, subTexture.leftBottomUV.y,
    };

    const GLuint indeces[]{
      // U  V
      0, 1, 2,
      2, 3, 0
    };

    m_vertexCoordsBuffer.init(vertexCoords, 2 * 4 * sizeof(GLfloat));
    VertexBufferLayout vertexCoordsLayout;
    vertexCoordsLayout.adLayoutEletmtntsFloat(2, false);
    m_vertexArray.addBuffer(m_vertexCoordsBuffer, vertexCoordsLayout);

    m_textureCoordsBuffer.init(textureCoords, 2 * 4 * sizeof(GLfloat));
    VertexBufferLayout textureCoordsLayout;
    textureCoordsLayout.adLayoutEletmtntsFloat(2, false);
    m_vertexArray.addBuffer(m_textureCoordsBuffer, textureCoordsLayout);

    m_idexBuffer.init(indeces, 6);

    m_vertexArray.unbind();
    m_idexBuffer.unbind();
  }

  Sprite::~Sprite() noexcept
  {
    //glDeleteVertexArrays(1, &m_VAO);
  }

  void Sprite::render(const glm::vec2 &position, const glm::vec2 &size, const float rotation, const float layer,
    const size_t frameId) const noexcept { 
    if(lastFrameId != frameId)
    {
      lastFrameId = frameId;
      const FrameDescription &currentFrameDescription = m_framesDescriptions[frameId];
      const GLfloat textureCoords[]{
        // U  V
        currentFrameDescription.leftBottomUV.x, currentFrameDescription.leftBottomUV.y,
        currentFrameDescription.leftBottomUV.x, currentFrameDescription.rightTopUV.y,
        currentFrameDescription.rightTopUV.x, currentFrameDescription.rightTopUV.y,
        currentFrameDescription.rightTopUV.x, currentFrameDescription.leftBottomUV.y,
      };
      m_textureCoordsBuffer.update(textureCoords, 2 * 4 * sizeof(GLfloat));
    }

    m_pShaderProgram->use();

    glm::mat4 model(1.f);
    model = glm::translate(model, glm::vec3(0.5f * size + position, 0.f));
    model = glm::rotate(model, glm::radians(rotation), glm::vec3(0.f, 0.f, 1.f));
    model = glm::translate(model, glm::vec3(-0.5f * size, 0.f));
    model = glm::scale(model, glm::vec3(size, 1.f));

    m_pShaderProgram->setMatrix4("modelMat", model);

    m_pShaderProgram->setFloat("layer", layer);

    glActiveTexture(GL_TEXTURE0);

    m_pTexture->bind();

    Renderer::draw(m_vertexArray, m_idexBuffer, *m_pShaderProgram);
  }

  Sprite::FrameDescription::FrameDescription(const glm::vec2 _leftBottomUV, const glm::vec2 _rightTopUV,
    const double _duration) noexcept : leftBottomUV(_leftBottomUV), rightTopUV(_rightTopUV),
    duration(_duration)
  {}

  double Sprite::getFrameDuration(const size_t frameId) const noexcept
  {
    return m_framesDescriptions[frameId].duration;
  }

  size_t Sprite::getFramesCount() const noexcept
  {
    return m_framesDescriptions.size();
  }
  void Sprite::insertFrames(std::vector<FrameDescription> framesDescriptions) noexcept
  {
    m_framesDescriptions = move(framesDescriptions);
  }
}