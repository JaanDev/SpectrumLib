#include "SpriteBatch.hpp"

#include "ShaderManager.hpp"

NS_SPECTRUM_BEGIN

SpriteBatch::SpriteBatch()
    : m_rects({}), m_texture(nullptr), m_shader(ShaderManager::instance()->getShader("sprite-shader")), m_color({255, 255, 255}),
      m_shouldRebuild(false) {}

void SpriteBatch::update(float dt) {
    if (m_shouldRebuild) {
        m_shouldRebuild = false;
        rebuild();
    }
}

void SpriteBatch::draw() {
    //
}

void SpriteBatch::rebuild() {
    //
}

NS_SPECTRUM_END
