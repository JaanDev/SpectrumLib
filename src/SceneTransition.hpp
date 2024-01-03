#pragma once
#include "utils.hpp"
#include "Scene.hpp"

NS_SPECTRUM_BEGIN

class SPL_API SceneTransition : public Scene {
  public:
    SceneTransition(std::shared_ptr<Scene> scene, float duration);

    virtual void update(float dt) override;

  protected:
    float m_duration;
    float m_runTime; // the time it was running
    std::shared_ptr<Scene> m_startScene;
    std::shared_ptr<Scene> m_endScene;
};

NS_SPECTRUM_END