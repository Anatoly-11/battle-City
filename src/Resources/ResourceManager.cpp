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
#include <rapidjson/document.h>
#include <rapidjson/error/en.h>
#include <filesystem>


using namespace std;

ResourceManager::ShaderProgramsMap ResourceManager::m_shaderPrograms;

ResourceManager::TextureMap ResourceManager::m_textures;

ResourceManager::SpritesMap ResourceManager::m_sprites;

vector <vector<string>> ResourceManager::m_levels;

std::vector<std::string> ResourceManager::m_startScreen;

std::string ResourceManager::m_path;

void ResourceManager::setExecutablePath(const std::string &executablePath) noexcept {
  m_path = filesystem::path{ executablePath }.parent_path().string();
}

void ResourceManager::unloadAllResources() noexcept {
  m_shaderPrograms.clear();
  m_textures.clear();
  m_sprites.clear();
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

shared_ptr<RenderEngine::ShaderProgram> ResourceManager::loadShader(const string &shaderName,
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
  shared_ptr<RenderEngine::ShaderProgram> &newShader =  m_shaderPrograms.emplace(shaderName,
    make_shared<RenderEngine::ShaderProgram>(vertexStr, fragmentStr)).first->second;
  if(!newShader->isCompiled()) {
    cerr << "Can't load shader program:\n"
      << "Vertex: " << vertexPath << '\n'
      << "Fragment: " << fragmentPath << endl;
    return nullptr;
  }
  return newShader;
}

shared_ptr<RenderEngine::ShaderProgram> ResourceManager::getShaderProgram(const string &shaderName) noexcept {
  auto it = m_shaderPrograms.find(shaderName);
  if(it == m_shaderPrograms.end()) {
    cerr << "Can't find the shader: " << shaderName << endl;
    return nullptr;
  }
  return it->second;
}

shared_ptr<RenderEngine::Texture2D> ResourceManager::loadTexture(const string &textureName,
  const string &texturePath) noexcept {
  int channels = 0;
  int width = 0;
  int height = 0;
  stbi_set_flip_vertically_on_load(true);
  if(unsigned char *pixels = stbi_load((m_path + '/' + texturePath).c_str(), &width, &height, &channels, 0);
    pixels != nullptr) {
    shared_ptr<RenderEngine::Texture2D> newTexture = m_textures.emplace(textureName, 
      make_shared<RenderEngine::Texture2D>(width, height, pixels, channels, GL_NEAREST,
        GL_CLAMP_TO_EDGE)).first->second;
    stbi_image_free(pixels);
    return newTexture;
  } else {
    cerr << "Can't load image: " << texturePath << " ..." << endl;
    return nullptr;
  }
}

shared_ptr<RenderEngine::Texture2D> ResourceManager::getTexture(const string &textureName) noexcept {
  auto it = m_textures.find(textureName);
  if(it == m_textures.end()) {
    cerr << "Can't find the texture: " << textureName << endl;
    return nullptr;
  }
  return it->second;
}

shared_ptr<RenderEngine::Sprite> ResourceManager::loadSprite(const std::string &spriteName,
  const std::string &textureName, const std::string &shaderName,  const std::string &subTextureName) noexcept {
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
  if(shared_ptr<RenderEngine::Sprite> newSprite = m_sprites.emplace(spriteName,
    make_shared<RenderEngine::Sprite>(pTexture, subTextureName, pShader)).first->second; newSprite != nullptr){
    return newSprite;
  }
  cerr << "Can't load the sprite: " << spriteName << " ..." << endl;
  return nullptr;
}

shared_ptr<RenderEngine::Sprite> ResourceManager::getSprite(const string &spriteName) noexcept{
  auto it = m_sprites.find(spriteName);
  if(it == m_sprites.end()) {
    cerr << "Can't find the sprite: " << spriteName << endl;
    return nullptr;
  }
  return it->second;
}

std::shared_ptr<RenderEngine::Texture2D> ResourceManager::loadTextureAtlas(const std::string &textureName,
  const std::string texturePath, std::vector<std::string> &subTextures, const unsigned int subTextureWidth,
  const unsigned int subTextureHeight) noexcept {
  auto pTexture = loadTexture(textureName, texturePath);
  if(pTexture) {
    const unsigned int textureWidth = pTexture->width();
    const unsigned int textureHeight = pTexture->height();
    unsigned int currentTextureOffsetX = 0;
    unsigned int currentTextureOffsetY = textureHeight;
    for(const auto &subTextureName : subTextures) {
      glm::vec2 leftBottom(static_cast<float>(currentTextureOffsetX + 0.01f) / textureWidth, 
        static_cast<float>(currentTextureOffsetY - subTextureHeight + 0.01f) / textureHeight);
      //0.01f correction!!!
      glm::vec2 rightTop(static_cast<float>(currentTextureOffsetX + subTextureWidth - 0.01f) / textureWidth,
        static_cast<float>(currentTextureOffsetY - 0.01f) / textureHeight);
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

  if(auto spritesIt = document.FindMember("sprites"); spritesIt != document.MemberEnd()) {
    for(const auto& currentSprite : spritesIt->value.GetArray()) {
      const string name = currentSprite["name"].GetString();
      const string textureAtlas = currentSprite["textureAtlas"].GetString();
      const string shader = currentSprite["shader"].GetString();
      const string initialSubTexture = currentSprite["initialSubTexture"].GetString();
      auto pSprite = loadSprite(name, textureAtlas, shader, initialSubTexture);
      if(!pSprite) {
        continue;
      }
      if(auto framesIt = currentSprite.FindMember("frames"); framesIt != currentSprite.MemberEnd())
      {
        const auto framesArray = framesIt->value.GetArray();
        vector<RenderEngine::Sprite::FrameDescription> framesDescriptions;
        framesDescriptions.reserve(framesArray.Size());
        for(const auto& currentFrame : framesArray) {
          const string subTextureStr = currentFrame["subTexture"].GetString();
          const double duration = currentFrame["duration"].GetDouble();
          const auto pTextureAtlas = getTexture(textureAtlas);
          const auto pSubTexture = pTextureAtlas->getSubTexture(subTextureStr);
          framesDescriptions.emplace_back(pSubTexture.leftBottomUV, pSubTexture.rightTopUV, duration);
        }
        pSprite->insertFrames(move(framesDescriptions));
      }
    }
  }

  if(auto startScreenIt = document.FindMember("start_screen"); startScreenIt != document.MemberEnd()) {
    const auto descriptionArray = startScreenIt->value.GetArray();
    m_startScreen.reserve(descriptionArray.Size());
    size_t maxLength = 0;
    for(const auto &currentRow : descriptionArray) {
      m_startScreen.emplace_back(currentRow.GetString());
      if(maxLength < m_startScreen.back().length()) {
        maxLength = m_startScreen.back().length();
      }
    }

    for(auto &currentRow : m_startScreen) {
      while(currentRow.length() < maxLength) {
        currentRow.append("F");
      }
    }
  }

  if(auto levelsIt = document.FindMember("levels"); levelsIt != document.MemberEnd()) {
    for(const auto& currentLevel : levelsIt->value.GetArray()) {
      const auto description = currentLevel["description"].GetArray();
      vector<string> levelRows;
      levelRows.reserve(description.Size());
      size_t maxLength = 0;
      for(const auto &currentRow : description) {
        size_t curLen = levelRows.emplace_back(currentRow.GetString()).length();
        if(curLen > maxLength) {
          maxLength = curLen;
        }
      }
      for(auto &currentRow : levelRows) {
        if(currentRow.length() < maxLength) {
          currentRow += string(maxLength - currentRow.length(), 'D');
        }
      }
      m_levels.emplace_back(move(levelRows));
    }
  }
  return true;
}

const vector<vector<string>> &ResourceManager::getLevels() noexcept {
  return m_levels;
}

const std::vector<std::string> &ResourceManager::getStartScreen() noexcept {
  return m_startScreen;
}

