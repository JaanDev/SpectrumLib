#pragma once
#include <vector>
#include <memory>
#include <string>
#include "utils.hpp"
#include "Texture.hpp"

NS_SPECTRUM_BEGIN

class Animation {
  public:
    Animation(float fps, std::vector<std::shared_ptr<Texture>> textures);
    Animation(float fps, const std::string& formatStr, int texCount);

    void update(float dt);
    std::shared_ptr<Texture> getTexture();

    inline void pause() { m_isPlaying = false; }
    inline void play() { m_isPlaying = true; }

  protected:
    float m_timeDelay;
    std::vector<std::shared_ptr<Texture>> m_textures;
    int m_texCount;
    float m_timeRun;
    int m_curTex;
    bool m_isPlaying;
};

NS_SPECTRUM_END