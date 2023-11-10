#include "ShaderManager.hpp"

NS_SPECTRUM_BEGIN

ShaderManager* ShaderManager::instance() {
    static auto inst = std::make_unique<ShaderManager>();
    return inst.get();
}

ShaderManager::ShaderManager() : m_shaders({}) {}

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
