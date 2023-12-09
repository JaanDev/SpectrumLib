#include "SpriteBatch.hpp"

#include <numeric>
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

void SpriteBatch::rebuild() {
    std::vector<float> vertices;

    for (const auto& quad : m_quads) {
        const auto& rect = quad.rect;
        const auto& tex = quad.texCoords;

        // clang-format off
        vertices.emplace_back(
            rect.x,          rect.y,          0.f, tex.x,         tex.y,
            rect.x,          rect.y + rect.h, 0.f, tex.x,         tex.y + tex.h,
            rect.x + rect.w, rect.y,          0.f, tex.x + tex.w, tex.y,
            rect.x + rect.w, rect.y + rect.h, 0.f, tex.x + tex.w, tex.y + tex.h
        );
        // clang-format on
    }

    std::vector<int> indices(4 * m_quads.size());
    std::iota(indices.begin(), indices.end(), 0);
}

NS_SPECTRUM_END
