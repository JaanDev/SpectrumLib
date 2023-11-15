#include "Sprite.hpp"

#include "TextureManager.hpp"
#include "logger.hpp"

NS_SPECTRUM_BEGIN

Sprite::Sprite(const std::string& path)
    : Node(), m_color({255, 255, 255}), m_shader(nullptr), m_blendFunc({GL_BLEND_SRC, GL_BLEND_DST}) {
    m_texture = std::make_shared<Texture>(path);
    m_boundingBox = m_texture->getSize();
}

Sprite::Sprite(std::shared_ptr<Texture> texture)
    : Node(), m_color({255, 255, 255}), m_shader(nullptr), m_blendFunc({GL_BLEND_SRC, GL_BLEND_DST}), m_texture(texture) {
    m_boundingBox = m_texture->getSize();
}

void Sprite::setBlendFunc(const BlendFunc& func) {}

void Sprite::draw() {
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, m_texture->getTextureID());

    // glColor3f(1.f, 0.f, 0.f);
    glBegin(GL_QUADS);
    glTexCoord2f(0, 0);
    glVertex2f(0, 0);
    glTexCoord2f(0, 1);
    glVertex2f(0, m_boundingBox.h);
    glTexCoord2f(1, 1);
    glVertex2f(m_boundingBox.w, m_boundingBox.h);
    glTexCoord2f(1, 0);
    glVertex2f(m_boundingBox.w, 0);
    glEnd();

    glBindTexture(GL_TEXTURE_2D, 0);
    glDisable(GL_TEXTURE_2D);
}

void Sprite::makeVBO() {
    // float points[] = {
    //     0.0f, 0.0f, 0.0f,
    //     0.0f, 1.0f, 0.0f,
    //     0.1f, 0.0f, 0.0f,
    //     0.1f, 1.0f, 0.0f,
    // };

    // float colors[] = {
    //     1.0f, 1.0f, 1.0f,
    //     1.0f, 1.0f, 1.0f,
    //     1.0f, 1.0f, 1.0f,
    //     1.0f, 1.0f, 1.0f,
    // };

    
}

NS_SPECTRUM_END
