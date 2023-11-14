#include "ShaderManager.hpp"

#include "logger.hpp"

NS_SPECTRUM_BEGIN

ShaderManager* ShaderManager::instance() {
    static auto inst = std::make_unique<ShaderManager>();
    return inst.get();
}

ShaderManager::ShaderManager() : m_shaders({}) {
#define STRINGIFY(...) #__VA_ARGS__

    auto defaultShader = std::make_shared<Shader>();
    defaultShader->loadFromString(R"(#version 330 core
layout(location = 0) in vec3 vertexPosition_modelspace;
void main() {
    gl_Position.xyz = vertexPosition_modelspace;
    gl_Position.w = 1.0;
})",
                                  R"(#version 330 core
out vec3 color;
void main() {
    color = vec3(1,0,0);
})");

    addShader(defaultShader, "builtin-shader");

#undef STRINGIFY
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
