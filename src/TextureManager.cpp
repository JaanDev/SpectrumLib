#include "TextureManager.hpp"
#include "FileManager.hpp"
#include <memory>
#include <rapidjson/document.h>
#include <fstream>

NS_SPECTRUM_BEGIN

TextureManager* TextureManager::instance() {
    static auto instance = std::make_unique<TextureManager>();
    return instance.get();
}

TextureManager::TextureManager() : m_textures({}), m_frames({}) {}

std::shared_ptr<Texture> TextureManager::getTexture(const std::string& name) {
    if(m_textures.count(name) == 0)
        addTexture(name);
    
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
    std::fstream stream(path);
    std::ostringstream osstream;
    osstream << stream.rdbuf();
    std::string json(osstream.str());

    rapidjson::Document doc;
    doc.Parse(json.c_str());
    
    auto texture = getTexture(doc["metadata"]["texture-filename"].GetString());

    for(auto& pair : doc["frames"].GetObj()){
        Recti rect = {
            pair.value["rect"].GetArray()[0].GetInt(),
            pair.value["rect"].GetArray()[1].GetInt(),
            pair.value["rect"].GetArray()[2].GetInt(),
            pair.value["rect"].GetArray()[3].GetInt()
        };

        m_frames[pair.name.GetString()] = std::make_shared<TextureFrame>(texture, rect, pair.value["rotated"].GetBool());
    }

}

void TextureManager::removeTexture(const std::string& name) {
    if (auto it = m_textures.find(name); it != m_textures.end())
        m_textures.erase(it);
}

void TextureManager::removeAllTextures() {
    m_textures.clear();
}

void TextureManager::removeFrame(const std::string& name) {
    if (auto it = m_frames.find(name); it != m_frames.end())
        m_frames.erase(it);
}

void TextureManager::removeFramesFromFile(const std::filesystem::path& path) {
    std::fstream stream(path);
    std::ostringstream osstream;
    osstream << stream.rdbuf();
    std::string json(osstream.str());

    rapidjson::Document doc;
    doc.Parse(json.c_str());
    
    for(auto& pair : doc["frames"].GetObj()){
        removeFrame(pair.name.GetString());
    }
}

NS_SPECTRUM_END
