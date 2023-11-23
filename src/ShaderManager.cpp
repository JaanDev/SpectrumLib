#include "ShaderManager.hpp"

#include "logger.hpp"

NS_SPECTRUM_BEGIN

ShaderManager* ShaderManager::instance() {
    static auto inst = std::make_unique<ShaderManager>();
    return inst.get();
}

ShaderManager::ShaderManager() : m_shaders({}) {
    std::string_view sprShaderVert = R"(
#version 330 core
layout (location = 0) in vec3 vertexPos;
layout (location = 1) in vec2 aTexCoord;
uniform mat4 mvp;

out vec2 texCoord;

void main() {
    gl_Position = mvp * vec4(vertexPos, 1.0);
    texCoord = aTexCoord;
}
)";
    std::string_view sprShaderFrag = R"(
#version 330 core

in vec2 texCoord;
uniform sampler2D tex;
uniform vec3 col;

void main() {
    gl_FragColor = texture(tex, texCoord) * vec4(col, 1.0);
}
)";

    auto sprShader = std::make_shared<Shader>();
    sprShader->loadFromString(sprShaderVert.data(), sprShaderFrag.data());

    addShader(sprShader, "sprite-shader");
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
