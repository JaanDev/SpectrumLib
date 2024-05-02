#include "ShaderManager.hpp"

#include "DefaultShaders.hpp"

NS_SPECTRUM_BEGIN

ShaderManager* ShaderManager::get() {
    static auto instance = ShaderManager();
    return &instance;
}

ShaderManager::ShaderManager() : m_shaders({}) {
    auto sprShader = std::make_shared<Shader>();
    sprShader->loadFromString(sprShaderVert.data(), sprShaderFrag.data());

    auto ttfShader = std::make_shared<Shader>();
    ttfShader->loadFromString(ttfShaderVert.data(), ttfShaderFrag.data());

    addShader(sprShader, "sprite-shader");
    addShader(ttfShader, "ttf-shader");
}

std::shared_ptr<Shader> ShaderManager::getShader(const std::string& id) const {
    return m_shaders.count(id) > 0 ? m_shaders.at(id) : nullptr;
}

void ShaderManager::addShader(std::shared_ptr<Shader> shader, const std::string& id) {
    m_shaders[id] = shader;
}

void ShaderManager::removeShader(const std::string& id) {
    if (auto it = m_shaders.find(id); it != m_shaders.end())
        m_shaders.erase(it);
}

void ShaderManager::removeAllShaders() {
    m_shaders.clear();
}

NS_SPECTRUM_END
