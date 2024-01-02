#include "SceneTransition.hpp"

#include "AppManager.hpp"

NS_SPECTRUM_BEGIN

SceneTransition::SceneTransition(std::shared_ptr<Scene> scene, float duration)
    : m_endScene(scene), m_duration(duration), m_startScene(AppManager::get()->getCurrentScene()), m_runTime(0.f) {}

void SceneTransition::update(float dt) {
    m_runTime += dt;
    if (m_runTime >= m_duration) {
        AppManager::get()->replaceScene(m_endScene);
    }
}

NS_SPECTRUM_END
