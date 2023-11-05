#include "Animation.hpp"

#include <fmt/format.h>
#include "TextureManager.hpp"

NS_SPECTRUM_BEGIN

Animation::Animation(float fps, std::vector<std::shared_ptr<Texture>> textures)
    : m_timeDelay(1.f / fps), m_textures(textures), m_timeRun(0.f), m_texCount(textures.size()), m_curTex(0), m_isPlaying(true) {}

Animation::Animation(float fps, const std::string& formatStr, int texCount)
    : m_timeDelay(1.f / fps), m_textures({}), m_timeRun(0.f), m_texCount(texCount), m_curTex(0), m_isPlaying(true) {
    for (auto i = 0; i < texCount; i++) {
        auto texName = fmt::format(formatStr, i);
        auto tex = TextureManager::instance()->getTexture(texName);
        if (tex)
            m_textures.push_back(tex);
    }
}

void Animation::update(float dt) {
    if (!m_isPlaying)
        return;

    m_timeRun += dt;
    m_curTex = static_cast<int>(m_timeRun / m_timeDelay) % m_texCount;
}

std::shared_ptr<Texture> Animation::getTexture() {
    return m_textures[m_curTex];
}

NS_SPECTRUM_END