#pragma once
#include <unordered_map>
#include <memory>
#include "utils.hpp"
#include "types.hpp"
#include "Texture.hpp"

NS_SPECTRUM_BEGIN

class TextureManager {
  public:
    static TextureManager* instance();

    // adds texture if not added previously
    std::shared_ptr<Texture> getTexture(const std::string& name);
    std::shared_ptr<Texture> addTexture(const std::string& path);
    std::shared_ptr<Texture> addTexture(const std::string& name, uint8_t* data, unsigned int dataLen);
    void addTexture(const std::string& name, std::shared_ptr<Texture> tex);

    // loads all textures to m_textures;
    void loadSpriteSheet(const std::string& path);

    void removeTexture(const std::string& name);
    void removeAllTextures();

  private:
    std::unordered_map<std::string, std::shared_ptr<Texture>> m_textures;
};

NS_SPECTRUM_END