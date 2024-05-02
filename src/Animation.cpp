#include "Animation.hpp"

#include <format>
#include "TextureManager.hpp"
#include "logger.hpp"

NS_SPECTRUM_BEGIN

std::shared_ptr<Animation> Animation::createWithFrames(float frameTime, int timesToRun, const std::vector<std::shared_ptr<TextureFrame>>& frames) {
    return std::make_shared<Animation>(frameTime, timesToRun, frames);
}

std::shared_ptr<Animation> Animation::createWithFrameNames(float frameTime, int timesToRun, const std::string& formatStr, int startNum, int endNum) {
    std::vector<std::shared_ptr<TextureFrame>> frames;

    for (auto i = startNum; i <= endNum; i++) {
        auto frameName = std::vformat(formatStr, std::make_format_args(i));
        auto frame = TextureManager::get()->getTextureFrame(frameName);
        if (frame) {
            frames.push_back(frame);
        } else {
            logW("Failed to find a texture frame for an animation with name {}", frameName);
        }
    }

    return Animation::createWithFrames(frameTime, timesToRun, frames);
}

void Animation::update(float dt) {
    m_isNewFrame = false;

    if (m_isFinished || !m_isPlaying || m_frameCount == 0)
        return;

    m_timeRun += dt;
    
    if (m_timeRun >= m_timeDelay) {
        m_timeRun -= m_timeDelay;
        m_curFrame++;
        m_isNewFrame = true;
    }

    if (m_curFrame >= m_frameCount) {
        if (m_timesLeft != -1)
            m_timesLeft--;

        if (m_timesLeft == 0) {
            m_isPlaying = false;
            m_isFinished = true;
        } else {
            m_curFrame = 0;
        }
    }
}

void Animation::goToFrame(int frame) {
    m_curFrame = frame;
    m_timeRun = m_timeDelay * frame;
}

std::shared_ptr<Texture> Animation::getTexture() const {
    return m_frames.size() > 0 ? m_frames[0]->getTexture() : nullptr;
}

Animation::Animation(float frameTime, int timesToRun, std::vector<std::shared_ptr<TextureFrame>> frames)
    : m_timeDelay(frameTime), m_timesLeft(timesToRun), m_frames(frames), m_timeRun(0.f), m_frameCount(frames.size()), m_curFrame(0),
      m_isPlaying(true), m_isFinished(false), m_isNewFrame(false) {}

NS_SPECTRUM_END