#pragma once
#include <vector>
#include <memory>
#include <string>
#include "utils.hpp"
#include "Texture.hpp"

NS_SPECTRUM_BEGIN

class Animation {
  public:
    // frameTime = 1.0 / fps
    Animation(float frameTime, int timesToRun, std::vector<std::shared_ptr<Texture>> textures);
    // frameTime = 1.0 / fps; inclusive
    Animation(float frameTime, int timesToRun, const std::string& formatStr, int startNum, int endNum);

    void update(float dt);
    std::shared_ptr<Texture> getTexture() const;
    void goToFrame(int frame);

    inline void pause() { m_isPlaying = false; }
    inline void play() { m_isPlaying = true; }

    inline bool isPlaying() const { return m_isPlaying; }
    inline bool isFinished() const { return m_isFinished; }
    inline int getCurrentFrame() const { return m_curTex; }

  protected:
    float m_timeDelay;
    std::vector<std::shared_ptr<Texture>> m_textures;
    int m_texCount;
    float m_timeRun;
    int m_timesLeft;
    int m_curTex;
    bool m_isPlaying;
    bool m_isFinished;
};

NS_SPECTRUM_END