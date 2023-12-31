#ifndef _RESOURCEMANAGER_H
#define _RESOURCEMANAGER_H 1.0

#include <string>
#include <memory>
#include <map>
#include <vector>

namespace RendererEngine {
  class ShaderProgram;
  class Texture2D;
  class Sprite;
  class AnimatedSprite;
}


class ResourceManager {
private:
  ResourceManager(const ResourceManager&) = delete;
  ResourceManager &operator=(const ResourceManager&) = delete;
  ~ResourceManager() = delete;
  ResourceManager() = delete;

  static std::string getFileString(const std::string &relativeFilePath) noexcept;

  using ShaderProgramsMap = std::map<std::string, std::shared_ptr<RendererEngine::ShaderProgram>>;
  static ShaderProgramsMap m_shaderPrograms;

  using TextureMap = std::map<std::string, std::shared_ptr<RendererEngine::Texture2D>>;
  static TextureMap m_textures;

  using SpritesMap = std::map<std::string, std::shared_ptr<RendererEngine::Sprite>>;
  static SpritesMap m_sprites;

  using AnimatedSpritesMap = std::map<std::string, std::shared_ptr<RendererEngine::AnimatedSprite>>;
  static AnimatedSpritesMap m_animatedSprites;

  static std::string m_path;
public:
  static void setExecutablePath(const std::string &executablePath) noexcept;

  static void unloadAllResources() noexcept;

  static std::shared_ptr<RendererEngine::ShaderProgram> getShaderProgram(const std::string &shaderName) noexcept;
 
  static std::shared_ptr<RendererEngine::ShaderProgram> loadShader(const std::string &shaderName,
    const std::string &vertexPath,const std::string &fragmentPath) noexcept;

  static std::shared_ptr<RendererEngine::Texture2D> loadTexture(const std::string &textureName,
    const std::string &texturePath) noexcept;

  static std::shared_ptr<RendererEngine::Texture2D> getTexture(const std::string &textureName) noexcept;

  static std::shared_ptr<RendererEngine::Sprite> loadSprite(const std::string &spriteName, const std::string &textureName,
    const std::string &shaderName, const unsigned int spriteWidth, const unsigned int spriteHeight,
    const std::string &subTextureName = "default") noexcept;

  static std::shared_ptr<RendererEngine::Sprite> getSprite(const std::string &spriteName) noexcept;

  static std::shared_ptr<RendererEngine::AnimatedSprite> loadAnimatedSprite(const std::string &animatedSpriteName, const std::string &textureName,
    const std::string &shaderName, const unsigned int spriteWidth, const unsigned int spriteHeight,
    const std::string &subTextureName = "default") noexcept;

  static std::shared_ptr<RendererEngine::AnimatedSprite> getAnimatedSprite(const std::string &animatedSpriteName) noexcept;

  static std::shared_ptr<RendererEngine::Texture2D> loadTextureAtlas(const std::string &textureName,
    const std::string texturePath, std::vector<std::string> &subTextures, const unsigned int subTextureWidth,
    const unsigned int subTextureHeight) noexcept;

  static bool loadJSONResources(const std::string &JSONPath) noexcept;
};
#endif // !_RESOURCEMANAGER_H