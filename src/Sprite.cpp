#include "Sprite.hpp"

NS_SPECTRUM_BEGIN

Sprite::Sprite(const std::string& path) : m_color({255, 255, 255}), m_shader(nullptr), m_blendFunc({GL_BLEND_SRC, GL_BLEND_DST}) {
    m_texture = std::make_shared<Texture>(path);
}

Sprite::Sprite(std::shared_ptr<Texture> texture)
    : m_color({255, 255, 255}), m_shader(nullptr), m_blendFunc({GL_BLEND_SRC, GL_BLEND_DST}), m_texture(texture) {}

void Sprite::setBlendFunc(const BlendFunc& func) {}

void Sprite::draw() {}

NS_SPECTRUM_END
