#include "TextureManager.hpp"
#include "FileManager.hpp"
#include <memory>


NS_SPECTRUM_BEGIN

TextureManager* TextureManager::instance() {
    static auto instance = std::make_unique<TextureManager>();
    return instance.get();
}

TextureManager::TextureManager() : m_textures({}), m_frames({}) {}

std::shared_ptr<Texture> TextureManager::getTexture(const std::string& name) {
    return m_textures.count(name) > 0 ? m_textures[name] : nullptr;
}

std::shared_ptr<TextureFrame> TextureManager::getTextureFrame(const std::string& name) {
    return m_frames.count(name) > 0 ? m_frames[name] : nullptr;
}

std::shared_ptr<Texture> TextureManager::addTexture(const std::filesystem::path& path) {
    auto tex = std::make_shared<Texture>(path.string());
    m_textures[path.filename().string()] = tex;
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

void TextureManager::loadSpriteSheet(const std::string& path) {
    addTexture("test.png");
    m_frames["part1.png"] = std::make_shared<TextureFrame>(getTexture("test.png"), Recti {0, 0, 128, 128}, false);
    m_frames["part2.png"] = std::make_shared<TextureFrame>(getTexture("test.png"), Recti {128, 0, 128, 128}, false);
    m_frames["part3.png"] = std::make_shared<TextureFrame>(getTexture("test.png"), Recti {0, 128, 128, 128}, false);
    m_frames["part4.png"] = std::make_shared<TextureFrame>(getTexture("test.png"), Recti {128, 128, 128, 128}, false);
}

void TextureManager::removeTexture(const std::string& name) {
    if (auto it = m_textures.find(name); it != m_textures.end())
        m_textures.erase(it);
}

void TextureManager::removeAllTextures() {
    m_textures.clear();
}

NS_SPECTRUM_END
