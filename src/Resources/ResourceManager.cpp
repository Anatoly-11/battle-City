#include "ResourceManager.h"
#include "../Renderer/ShaderProgram.h"
#include <sstream>
#include <fstream>
#include <iostream>
#define STB_IMAGE_IMPLEMENTATION
#define STBI_ONLY_PNG
#include "stb_image.h"
#include "../Renderer/Texture2D.h"
#include "../Renderer/Sprite.h"
#include "../Renderer/AnimatedSprite.h"
#include <rapidjson/document.h>
#include <rapidjson/error/en.h>


using namespace std;

ResourceManager::ShaderProgramsMap ResourceManager::m_shaderPrograms;

ResourceManager::TextureMap ResourceManager::m_textures;

ResourceManager::SpritesMap ResourceManager::m_sprites;

ResourceManager::AnimatedSpritesMap ResourceManager::m_animatedSprites;

std::string ResourceManager::m_path;

void ResourceManager::setExecutablePath(const std::string &executablePath) noexcept {
  size_t found = executablePath.find_last_of("/\\");
  m_path = executablePath.substr(0, found);
}

void ResourceManager::unloadAllResources() noexcept {
  m_shaderPrograms.clear();
  m_textures.clear();
  m_sprites.clear();
  m_animatedSprites.clear();
  m_path.clear();
}

string ResourceManager::getFileString(const string &relativeFilePath) noexcept {
  ifstream f;
  f.open(m_path + '/' + relativeFilePath.c_str(), ios::in | ios::binary);
  if(!f.is_open()) {
    cerr << "Failed to open file: " << relativeFilePath << endl;
    return "";
  }
  stringstream buf;
  buf << f.rdbuf();
  return buf.str();
}

shared_ptr<RendererEngine::ShaderProgram> ResourceManager::loadShader(const string &shaderName,
  const string &vertexPath, const string &fragmentPath) noexcept {
  string vertexStr = getFileString(vertexPath);
  if(vertexStr == "") {
    cerr << "No vertex shader..." << endl;
    return nullptr;
  }
  string fragmentStr = getFileString(fragmentPath);
  if(fragmentStr == "") {
    cerr << "No fragment shader..." << endl;
    return nullptr;
  }
  shared_ptr<RendererEngine::ShaderProgram> &newShader =  m_shaderPrograms.emplace(shaderName,
    make_shared<RendererEngine::ShaderProgram>(vertexStr, fragmentStr)).first->second;
  if(!newShader->isCompiled()) {
    cerr << "Can't load shader program:\n"
      << "Vertex: " << vertexPath << '\n'
      << "Fragment: " << fragmentPath << endl;
    return nullptr;
  }
  return newShader;
}

shared_ptr<RendererEngine::ShaderProgram> ResourceManager::getShaderProgram(const string &shaderName) noexcept {
  auto it = m_shaderPrograms.find(shaderName);
  if(it == m_shaderPrograms.end()) {
    cerr << "Can't find the shader: " << shaderName << endl;
    return nullptr;
  }
  return it->second;
}

shared_ptr<RendererEngine::Texture2D> ResourceManager::loadTexture(const string &textureName,
  const string &texturePath) noexcept {
  int channels = 0;
  int width = 0;
  int height = 0;
  stbi_set_flip_vertically_on_load(true);
  if(unsigned char *pixels = stbi_load((m_path + '/' + texturePath).c_str(), &width, &height, &channels, 0);
    pixels != nullptr) {
    shared_ptr<RendererEngine::Texture2D> newTexture = m_textures.emplace(textureName, 
      make_shared<RendererEngine::Texture2D>(width, height, pixels, channels, GL_NEAREST,
        GL_CLAMP_TO_EDGE)).first->second;
    stbi_image_free(pixels);
    return newTexture;
  } else {
    cerr << "Can't load image: " << texturePath << " ..." << endl;
    return nullptr;
  }
}

shared_ptr<RendererEngine::Texture2D> ResourceManager::getTexture(const string &textureName) noexcept {
  auto it = m_textures.find(textureName);
  if(it == m_textures.end()) {
    cerr << "Can't find the texture: " << textureName << endl;
    return nullptr;
  }
  return it->second;
}

shared_ptr<RendererEngine::Sprite> ResourceManager::loadSprite(const std::string &spriteName,
  const std::string &textureName, const std::string &shaderName, const unsigned int spriteWidth,
  const unsigned int spriteHeight, const std::string &subTextureName) noexcept {
  auto pTexture = getTexture(textureName);
  if(pTexture == nullptr) {
    cerr << "Can't find the texture: " << textureName << " for the sprite: " << spriteName << endl;
    return nullptr;
  }
  auto pShader = getShaderProgram(shaderName);
  if(pShader == nullptr) {
    cerr << "Can't find the shader: " << shaderName << " for the sprite: " << spriteName << endl;
    return nullptr;
  }
  if(shared_ptr<RendererEngine::Sprite> newSprite = m_sprites.emplace(spriteName,
    make_shared<RendererEngine::Sprite>(pTexture, subTextureName, pShader, glm::vec2(0.f, 0.f),
      glm::vec2(spriteWidth, spriteHeight))).first->second; newSprite != nullptr){
    return newSprite;
  }
  cerr << "Can't load the sprite: " << spriteName << " ..." << endl;
  return nullptr;
}

shared_ptr<RendererEngine::Sprite> ResourceManager::getSprite(const string &spriteName) noexcept{
  auto it = m_sprites.find(spriteName);
  if(it == m_sprites.end()) {
    cerr << "Can't find the sprite: " << spriteName << endl;
    return nullptr;
  }
  return it->second;
}

shared_ptr<RendererEngine::AnimatedSprite> ResourceManager::loadAnimatedSprite(const std::string &animatedSpriteName,
  const std::string &textureName, const std::string &shaderName, const unsigned int spriteWidth,
  const unsigned int spriteHeight, const std::string &subTextureName) noexcept {
  auto pTexture = getTexture(textureName);
  if(pTexture == nullptr) {
    cerr << "Can't find the texture: " << textureName << " for the animated sprite: " << animatedSpriteName << endl;
    return nullptr;
  }
  auto pShader = getShaderProgram(shaderName);
  if(pShader == nullptr) {
    cerr << "Can't find the shader: " << shaderName << " for the sprite: " << animatedSpriteName << endl;
    return nullptr;
  }
  if(shared_ptr<RendererEngine::AnimatedSprite> newSprite = m_animatedSprites.emplace(animatedSpriteName,
    make_shared<RendererEngine::AnimatedSprite>(pTexture, subTextureName, pShader, glm::vec2(0.f, 0.f),
      glm::vec2(spriteWidth, spriteHeight))).first->second; newSprite != nullptr){
    return newSprite;
  }
  cerr << "Can't load the sprite: " << animatedSpriteName << " ..." << endl;
  return nullptr;
}

shared_ptr<RendererEngine::AnimatedSprite> ResourceManager::getAnimatedSprite(
  const string &animatedSpriteName) noexcept{
  auto it = m_animatedSprites.find(animatedSpriteName);
  if(it == m_animatedSprites.end()) {
    cerr << "Can't find the animated sprite: " << animatedSpriteName << endl;
    return nullptr;
  }
  return it->second;
}

std::shared_ptr<RendererEngine::Texture2D> ResourceManager::loadTextureAtlas(const std::string &textureName,
  const std::string texturePath, std::vector<std::string> &subTextures, const unsigned int subTextureWidth,
  const unsigned int subTextureHeight) noexcept {
  auto pTexture = loadTexture(textureName, texturePath);
  if(pTexture) {
    const unsigned int textureWidth = pTexture->width();
    const unsigned int textureHeight = pTexture->height();
    unsigned int currentTextureOffsetX = 0;
    unsigned int currentTextureOffsetY = textureHeight;
    for(const auto &subTextureName : subTextures) {
      glm::vec2 leftBottom(static_cast<float>(currentTextureOffsetX) / textureWidth, 
        static_cast<float>(currentTextureOffsetY - subTextureHeight) / textureHeight);

      glm::vec2 rightTop(static_cast<float>(currentTextureOffsetX + subTextureWidth) / textureWidth,
        static_cast<float>(currentTextureOffsetY) / textureHeight);
      pTexture->addSubTexture(subTextureName, leftBottom, rightTop);
      currentTextureOffsetX += subTextureWidth;
      if(currentTextureOffsetX >= textureWidth) {
        currentTextureOffsetX = 0;
        currentTextureOffsetY -= subTextureHeight;
      }
    }
  }
  return pTexture;
}

bool ResourceManager::loadJSONResources(const string &JSONPath) noexcept {
  
  string JSONString = getFileString(JSONPath);
  if(JSONString.empty()) {
    cerr << "No JSON resource file..." << endl;
    return false;
  }

  rapidjson::Document document;
  rapidjson::ParseResult parseResult = document.Parse(JSONString.c_str());
  if(!parseResult) {
    cerr << "JSON parse error: " << rapidjson::GetParseError_En(parseResult.Code())
      << " (" << parseResult.Offset() << ")\nIn file: " << JSONPath << endl;
    return false;
  }

  if(auto sadersIt = document.FindMember("shaders"); sadersIt != document.MemberEnd()) {
    for(const auto& currentShader : sadersIt->value.GetArray()) {
      const string name = currentShader["name"].GetString();
      const string filePath_v = currentShader["filePath_v"].GetString();
      const string filePath_f = currentShader["filePath_f"].GetString();
      loadShader(name, filePath_v, filePath_f);
    }
  }

  if(auto textureAtlasisIt = document.FindMember("textureAtlases"); textureAtlasisIt != document.MemberEnd()) {
    for(const auto& currentTextureAtlas : textureAtlasisIt->value.GetArray()) {
      const string name = currentTextureAtlas["name"].GetString();
      const string filePath = currentTextureAtlas["filePath"].GetString();
      const unsigned int subTextureWidth = currentTextureAtlas["subTextureWidth"].GetUint();
      const unsigned int subTextureHeight = currentTextureAtlas["subTextureHeight"].GetUint();

      const auto subTexturesArray = currentTextureAtlas["subTextures"].GetArray();
      vector<string> subTextures;
      subTextures.reserve(subTexturesArray.Size());
      for(const auto &cuttentSubTexture : subTexturesArray) {
        subTextures.emplace_back(cuttentSubTexture.GetString());
      }
      loadTextureAtlas(name, filePath, subTextures, subTextureWidth, subTextureHeight);
    }
  }

  if(auto animatedSpritesIt = document.FindMember("animatedSprites"); animatedSpritesIt
    != document.MemberEnd()) {
    for(const auto& currentAnimatedSprite : animatedSpritesIt->value.GetArray()) {
      const string name = currentAnimatedSprite["name"].GetString();
      const string textureAtlas = currentAnimatedSprite["textureAtlas"].GetString();
      const string shader = currentAnimatedSprite["shader"].GetString();
      const unsigned int initialWidth = currentAnimatedSprite["initialWidth"].GetUint();
      const unsigned int initialHeight = currentAnimatedSprite["initialHeight"].GetUint();
      const string initialSubTexture = currentAnimatedSprite["initialSubTexture"].GetString();
      auto pAnimatedSprite = loadAnimatedSprite(name, textureAtlas, shader, initialWidth, initialHeight,
        initialSubTexture);
      if(!pAnimatedSprite) {
        continue;
      }
      const auto statesArray = currentAnimatedSprite["states"].GetArray();
      for(const auto& currentState : statesArray) {
        const string stateName = currentState["stateName"].GetString();
        vector<pair<string, uint64_t>> frames;
        const auto framesArray = currentState["frames"].GetArray();
        frames.reserve(framesArray.Size());
        for(const auto& currentFrame : framesArray) {
          const string subTesture = currentFrame["subTesture"].GetString();
          const uint64_t duration = currentFrame["duration"].GetUint64();
          frames.emplace_back(pair<string, uint64_t>(subTesture, duration));
        }
        pAnimatedSprite->insertState(stateName, frames);
      }
    }
  }

  if(auto levelsIt = document.FindMember("levels"); levelsIt != document.MemberEnd()) {
    for(const auto& currentLevel : levelsIt->value.GetArray()) {
      const auto description = currentLevel["description"].GetArray();
      vector<string> levelRows;
      levelRows.reserve(description.Size());
      for(const auto& currentRoow : description) {
        levelRows.emplace_back(currentRoow.GetString());
      }
      //TODO...
    }
  }
  return true;
}