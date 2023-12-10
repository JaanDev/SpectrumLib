#include "SpriteBatch.hpp"

#include <numeric>
#include "logger.hpp"
#include "ShaderManager.hpp"

NS_SPECTRUM_BEGIN

SpriteBatch::SpriteBatch()
    : m_quads({}), m_texture(nullptr), m_shader(ShaderManager::instance()->getShader("sprite-shader")), m_color({255, 255, 255}),
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

void SpriteBatch::addRect(const BatchQuad& rect) {
    m_quads.push_back(rect);
    m_shouldRebuild = true;
}

void SpriteBatch::rebuild() {
    std::vector<float> vertices;

    for (const auto& quad : m_quads) {
        auto& rect = quad.rect;
        auto& tex = quad.texCoords;

        // clang-format off
        vertices.insert(vertices.end(), {
            rect.x,          rect.y,          0.f, tex.x,         tex.y,
            rect.x,          rect.y + rect.h, 0.f, tex.x,         tex.y + tex.h,
            rect.x + rect.w, rect.y,          0.f, tex.x + tex.w, tex.y,
            rect.x + rect.w, rect.y + rect.h, 0.f, tex.x + tex.w, tex.y + tex.h
        });
        // clang-format on
    }

    std::vector<unsigned int> indices(6 * m_quads.size());

    for (auto i = 0u; i < m_quads.size(); i++) {
        auto idx = i * 4;
        indices.insert(indices.end(), {idx, idx + 1, idx + 2, idx + 1, idx + 2, idx + 3});
    }

    
}

NS_SPECTRUM_END
