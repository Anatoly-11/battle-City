#pragma once
#ifndef _RESOURCEMANAGER_H
#define _RESOURCEMANAGER_H 1.0

#include <string>
#include <memory>
#include <map>
#include <vector>

namespace Renderer {
  class ShaderProgram;
  class Texture2D;
  class Sprite;
  class AnimatedSprite;
}


class ResourceManager {
private:
  std::string getFileString(const std::string &relativeFilePath) const noexcept;

  using ShaderProgramsMap = std::map<std::string, std::shared_ptr<Renderer::ShaderProgram>>;
  ShaderProgramsMap m_shaderPrograms;

  using TextureMap = std::map<std::string, std::shared_ptr<Renderer::Texture2D>>;
  TextureMap m_textures;

  using SpritesMap = std::map<std::string, std::shared_ptr<Renderer::Sprite>>;
  SpritesMap m_sprites;

  using AnimatedSpritesMap = std::map<std::string, std::shared_ptr<Renderer::AnimatedSprite>>;
  AnimatedSpritesMap m_animatedSprites;

  std::string m_path;
public:
  ResourceManager(const std::string &executablePath) noexcept;

  ResourceManager() = delete;

  ~ResourceManager() noexcept;
  
  std::shared_ptr<Renderer::ShaderProgram> getShaderProgram(const std::string &shaderName) const noexcept;
 
  std::shared_ptr<Renderer::ShaderProgram> loadShader(const std::string &shaderName,
    const std::string &vertexPath,const std::string &fragmentPath) noexcept;

  std::shared_ptr<Renderer::Texture2D> loadTexture(const std::string &textureName,
    const std::string &texturePath) noexcept;

  std::shared_ptr<Renderer::Texture2D> getTexture(const std::string &textureName) const noexcept;

  std::shared_ptr<Renderer::Sprite> loadSprite(const std::string &spriteName, const std::string &textureName,
    const std::string &shaderName, const unsigned int spriteWidth, const unsigned int spriteHeight,
    const std::string &subTextureName = "default") noexcept;

  std::shared_ptr<Renderer::Sprite> getSprite(const std::string &spriteName) const noexcept;

  std::shared_ptr<Renderer::AnimatedSprite> loadAnimatedSprite(const std::string &animatedSpriteName, const std::string &textureName,
    const std::string &shaderName, const unsigned int spriteWidth, const unsigned int spriteHeight,
    const std::string &subTextureName = "default") noexcept;

  std::shared_ptr<Renderer::AnimatedSprite> getAnimatedSprite(const std::string &animatedSpriteName) const noexcept;

  std::shared_ptr<Renderer::Texture2D> loadTextureAtlas(const std::string &textureName,
    const std::string texturePath, std::vector<std::string> &subTextures, const unsigned subTextureWidth,
    const unsigned subTextureHeight) noexcept;
};
#endif // !_RESOURCEMANAGER_H