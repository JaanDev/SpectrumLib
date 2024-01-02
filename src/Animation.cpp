#include "Animation.hpp"

#include <fmt/format.h>
#include "TextureManager.hpp"
#include "logger.hpp"

NS_SPECTRUM_BEGIN

Animation::Animation(float frameTime, int timesToRun, std::vector<std::shared_ptr<Texture>> textures)
    : m_timeDelay(frameTime), m_timesLeft(timesToRun), m_textures(textures), m_timeRun(0.f), m_texCount(textures.size()),
      m_curTex(0), m_isPlaying(true), m_isFinished(false) {}

Animation::Animation(float frameTime, int timesToRun, const std::string& formatStr, int startNum, int endNum)
    : m_timeDelay(frameTime), m_timesLeft(timesToRun), m_textures({}), m_timeRun(0.f), m_curTex(0), m_isPlaying(true),
      m_isFinished(false) {

    for (auto i = startNum; i <= endNum; i++) {
        auto texName = fmt::format(fmt::runtime(formatStr), i);
        auto tex = TextureManager::get()->getTexture(texName);
        if (tex) {
            m_textures.push_back(tex);
        } else {
            logW("Failed to find a texture for an animation with texture name {}", texName);
        }
    }

    m_texCount = m_textures.size();
}

void Animation::update(float dt) {
    if (m_isFinished || !m_isPlaying || m_texCount == 0)
        return;

    m_timeRun += dt;
    m_curTex = static_cast<int>(m_timeRun / m_timeDelay);

    if (m_curTex >= m_texCount) {
        m_timesLeft--;

        if (m_timesLeft == 0) {
            m_isPlaying = false;
            m_isFinished = true;
        } else {
            m_curTex = 0;
            m_timeRun = 0.f;
        }
    }
}

std::shared_ptr<Texture> Animation::getTexture() const {
    return m_textures[m_curTex];
}

void Animation::goToFrame(int frame) {
    m_curTex = frame;
    m_timeRun = m_timeDelay * frame;
}

NS_SPECTRUM_END