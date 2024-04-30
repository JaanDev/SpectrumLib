#pragma once
#include <vector>
#include <memory>
#include <string>
#include "utils.hpp"
#include "Texture.hpp"
#include "TextureFrame.hpp"

NS_SPECTRUM_BEGIN

class SPL_API Animation {
  public:
    static std::shared_ptr<Animation> createWithFrames(float frameTime, int timesToRun, const std::vector<std::shared_ptr<TextureFrame>>& frames);
    static std::shared_ptr<Animation> createWithFrameNames(float frameTime, int timesToRun, const std::string& formatStr, int startNum, int endNum);
    Animation(float frameTime, int timesToRun, std::vector<std::shared_ptr<TextureFrame>> frames);

    void update(float dt);
    inline std::shared_ptr<TextureFrame> getFrame() const { return m_frames[m_curFrame]; };
    void goToFrame(int frame);

    inline void pause() { m_isPlaying = false; }
    inline void play() { m_isPlaying = true; }
    inline bool isPlaying() const { return m_isPlaying; }

    inline bool isFinished() const { return m_isFinished; }
    inline int getCurrentFrame() const { return m_curFrame; }
    inline bool isNewFrame() const { return m_isNewFrame; }

  protected:
    std::vector<std::shared_ptr<TextureFrame>> m_frames;
    float m_timeDelay;
    int m_frameCount;
    float m_timeRun;
    int m_timesLeft;
    int m_curFrame;
    bool m_isPlaying;
    bool m_isFinished;
    bool m_isNewFrame;
};

NS_SPECTRUM_END