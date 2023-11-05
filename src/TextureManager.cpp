#include "TextureManager.hpp"

#include <memory>

NS_SPECTRUM_BEGIN

TextureManager* TextureManager::instance() {
    static auto instance = std::make_unique<TextureManager>();
    return instance.get();
}

TextureManager::TextureManager() : m_textures({}) {}

std::shared_ptr<Texture> TextureManager::getTexture(const std::string& name) {
    return m_textures.count(name) > 0 ? m_textures[name] : nullptr;
}

std::shared_ptr<Texture> TextureManager::addTexture(const std::string& path) {
    auto tex = std::make_shared<Texture>(path);
    m_textures[path] = tex;
    return tex;
}

std::shared_ptr<Texture> TextureManager::addTexture(const std::string& name, uint8_t* data, unsigned int dataLen) {
    auto tex = std::make_shared<Texture>(data, dataLen);
    m_textures[name] = tex;
    return tex;
}

void TextureManager::addTexture(const std::string& name, std::shared_ptr<Texture> tex) {
    m_textures[name] = tex;
}

void TextureManager::loadSpriteSheet(const std::string& path) {}

void TextureManager::removeTexture(const std::string& name) {
    if (auto it = m_textures.find(name); it != m_textures.end())
        m_textures.erase(it);
}

void TextureManager::removeAllTextures() {
    m_textures.clear();
}

NS_SPECTRUM_END
