#ifndef _RESOURCEMANAGER_H
#define _RESOURCEMANAGER_H 1.0

#include <string>
#include <memory>
#include <map>
#include <vector>

namespace RenderEngine {
  class ShaderProgram;
  class Texture2D;
  class Sprite;
}

class ResourceManager {
  ResourceManager(const ResourceManager&) = delete;
  ResourceManager &operator=(const ResourceManager&) = delete;
  ResourceManager(ResourceManager&&) = delete;
  ResourceManager &operator=(ResourceManager&&) = delete;
  ~ResourceManager() = delete;
  ResourceManager() = delete;
public:
  static void setExecutablePath(const std::string &executablePath) noexcept;

  static void unloadAllResources() noexcept;

  static std::shared_ptr<RenderEngine::ShaderProgram> getShaderProgram(const std::string &shaderName) noexcept;
 
  static std::shared_ptr<RenderEngine::ShaderProgram> loadShader(const std::string &shaderName,
    const std::string &vertexPath,const std::string &fragmentPath) noexcept;

  static std::shared_ptr<RenderEngine::Texture2D> loadTexture(const std::string &textureName,
    const std::string &texturePath) noexcept;

  static std::shared_ptr<RenderEngine::Texture2D> getTexture(const std::string &textureName) noexcept;

  static std::shared_ptr<RenderEngine::Sprite> loadSprite(const std::string &spriteName, const std::string &textureName,
    const std::string &shaderName, const std::string &subTextureName = "default") noexcept;

  static std::shared_ptr<RenderEngine::Sprite> getSprite(const std::string &spriteName) noexcept;

  static std::shared_ptr<RenderEngine::Texture2D> loadTextureAtlas(const std::string &textureName,
    const std::string texturePath, std::vector<std::string> &subTextures, const unsigned int subTextureWidth,
    const unsigned int subTextureHeight) noexcept;

  static bool loadJSONResources(const std::string &JSONPath) noexcept;

  static const std::vector <std::vector<std::string>> &getLevels() noexcept;

  static const std::vector<std::string> &getStartScreen() noexcept;

private:

  static std::string getFileString(const std::string &relativeFilePath) noexcept;

  using ShaderProgramsMap = std::map<std::string, std::shared_ptr<RenderEngine::ShaderProgram>>;
  static ShaderProgramsMap m_shaderPrograms;

  using TextureMap = std::map<std::string, std::shared_ptr<RenderEngine::Texture2D>>;
  static TextureMap m_textures;

  using SpritesMap = std::map<std::string, std::shared_ptr<RenderEngine::Sprite>>;
  static SpritesMap m_sprites;

  static std::vector <std::vector<std::string>> m_levels;

  static std::vector<std::string> m_startScreen;

  static std::string m_path;
};
#endif // !_RESOURCEMANAGER_H