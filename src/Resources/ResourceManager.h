#pragma once
#ifndef _RESOURCEMANAGER_H
#define _RESOURCEMANAGER_H 1.0
//-------------------------------------------------------------------------------------------------------------
#include <string>
#include <memory>
#include <map>
//-------------------------------------------------------------------------------------------------------------
namespace Renderer {
  class ShaderProgram;
  class Texture2D;
  class Sprite;
}
//-------------------------------------------------------------------------------------------------------------
class ResourceManager {
#pragma region Invisible
public:
  ~ResourceManager() noexcept = default;
  ResourceManager(const ResourceManager&) = delete;
  ResourceManager &operator=(const ResourceManager&) = delete;
  ResourceManager(ResourceManager&&) = delete;
  ResourceManager &operator=(ResourceManager&&) = delete;
#pragma endregion
private:
  std::string getFileString(const std::string &relativeFilePath) const noexcept;

  using ShaderProgramsMap = std::map<std::string, std::shared_ptr<Renderer::ShaderProgram>>;
  ShaderProgramsMap m_shaderPrograms;

  using TextureMap = std::map<std::string, std::shared_ptr<Renderer::Texture2D>>;
  TextureMap m_textures;

  using SpritesMap = std::map<std::string, std::shared_ptr<Renderer::Sprite>>;
  SpritesMap m_sprites;

  std::string m_path;
public:
  ResourceManager(const std::string &executablePath) noexcept;
  std::shared_ptr<Renderer::ShaderProgram> getShaderProgram(const std::string &shaderName) noexcept;
    std::shared_ptr<Renderer::ShaderProgram> loadShader(const std::string &shaderName, 
    const std::string &vertexPath,const std::string &fragmentPath) noexcept;

  std::shared_ptr<Renderer::Texture2D> loadTexture(const std::string &textureName, const std::string &texturePath)  noexcept;
  std::shared_ptr<Renderer::Texture2D> getTexture(const std::string &textureName) const noexcept;

  std::shared_ptr<Renderer::Sprite> loadSprite(const std::string &spriteName, const std::string &textureName,
    const std::string &shaderName, const unsigned int spriteWidth, const unsigned int spriteHeight) noexcept;
  std::shared_ptr<Renderer::Sprite> getSprite(const std::string &spriteName) const noexcept;
};
//-------------------------------------------------------------------------------------------------------------
#endif // !_RESOURCEMANAGER_H
//-------------------------------------------------------------------------------------------------------------