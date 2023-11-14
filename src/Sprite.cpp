#include "Sprite.hpp"

#include "TextureManager.hpp"
#include "logger.hpp"

NS_SPECTRUM_BEGIN

Sprite::Sprite(const std::string& path) : Node(), m_color({255, 255, 255}), m_shader(nullptr), m_blendFunc({GL_BLEND_SRC, GL_BLEND_DST}) {
    m_texture = std::make_shared<Texture>(path);
    m_boundingBox = m_texture->getSize();
}

Sprite::Sprite(std::shared_ptr<Texture> texture)
    : Node(), m_color({255, 255, 255}), m_shader(nullptr), m_blendFunc({GL_BLEND_SRC, GL_BLEND_DST}), m_texture(texture) {
    m_boundingBox = m_texture->getSize();
}

void Sprite::setBlendFunc(const BlendFunc& func) {}

void Sprite::draw() {
    glColor3f(1.f, 0.f, 0.f);
    glBegin(GL_QUADS);
    glVertex2f(0, 0);
    glVertex2f(0, m_boundingBox.h);
    glVertex2f(m_boundingBox.w, m_boundingBox.h);
    glVertex2f(m_boundingBox.w, 0);
    glEnd();
}

NS_SPECTRUM_END
