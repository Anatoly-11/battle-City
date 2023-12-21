#include "ResourceManager.h"
#include "../Renderer/ShaderProgram.h"
#include <sstream>
#include <fstream>
#include <iostream>
#define STB_IMAGE_IMPLEMENTATION
#define STBI_ONLY_PNG
#include "stb_image.h"
#include "../Renderer/Texture2D.h"
//-------------------------------------------------------------------------------------------------------------
using namespace std;
//-------------------------------------------------------------------------------------------------------------
ResourceManager :: ResourceManager(const std::string &executablePath) noexcept {
  size_t found = executablePath.find_last_of("/\\");
  m_path = executablePath.substr(0, found);
}
//-------------------------------------------------------------------------------------------------------------
string ResourceManager::getFileString(const string &relativeFilePath) const noexcept {
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
//-------------------------------------------------------------------------------------------------------------
shared_ptr<Renderer::ShaderProgram> ResourceManager :: loadShaders(const string &shaderName,
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
  shared_ptr<Renderer::ShaderProgram> &newShader =  m_shaderPrograms.emplace(shaderName, 
    make_shared<Renderer::ShaderProgram>(vertexStr, fragmentStr)).first->second;
  if(!newShader->isCompiled()) {
    cerr << "Can't load shader program:\n"
      << "Vertex: " << vertexPath << '\n'
      << "Fragment: " << fragmentPath << endl;
    return nullptr;
  }
  return newShader;

}
//-------------------------------------------------------------------------------------------------------------
shared_ptr<Renderer::ShaderProgram> ResourceManager::getShaderProgram(const string &shaderName) noexcept {
  auto it = m_shaderPrograms.find(shaderName);
  if(it == m_shaderPrograms.end()) {
    cerr << "Can't find the shader: " << shaderName << endl;
    return nullptr;
  }
  return it->second;
}
//-------------------------------------------------------------------------------------------------------------
shared_ptr<Renderer::Texture2D> ResourceManager::loadTexture(const string & textureName, const string & texturePath) noexcept {
  int channels = 0;
  int width = 0;
  int height = 0;
  stbi_set_flip_vertically_on_load(true);
  if(unsigned char *pixels = stbi_load((m_path + '/' + texturePath).c_str(), &width, &height, &channels, 0);
    pixels != nullptr) {
    shared_ptr<Renderer::Texture2D> newTexture = m_textureMap.emplace(textureName, 
      make_shared<Renderer::Texture2D>(width, height, pixels, channels, GL_NEAREST, GL_CLAMP_TO_EDGE)).first->second;
    stbi_image_free(pixels);
    return newTexture;
  } else {
    cerr << "Can't load image: " << texturePath << " ..." << endl;
    return nullptr;
  }
}
//-------------------------------------------------------------------------------------------------------------
shared_ptr<Renderer::Texture2D> ResourceManager::getTexture(const string &textureName) noexcept{
  auto it = m_textureMap.find(textureName);
  if(it == m_textureMap.end()) {
    cerr << "Can't find the texture: " << textureName << endl;
    return nullptr;
  }
  return it->second;
}
//-------------------------------------------------------------------------------------------------------------