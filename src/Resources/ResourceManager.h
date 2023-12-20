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
  std::string m_path;
public:
  ResourceManager(const std::string &executablePath) noexcept;
  std::shared_ptr<Renderer::ShaderProgram> loadShaders(const std::string &shaderName, 
    const std::string &vertexPath,const std::string &fragmentPath) noexcept;
  std::shared_ptr<Renderer::ShaderProgram> getShaderProgram(const std::string &shaderName) noexcept;

};
//-------------------------------------------------------------------------------------------------------------
#endif // !_RESOURCEMANAGER_H
//-------------------------------------------------------------------------------------------------------------