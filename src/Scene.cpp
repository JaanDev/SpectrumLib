#include "Scene.hpp"

#include "AppManager.hpp"

NS_SPECTRUM_BEGIN

Scene::Scene() : Node(), m_bgColor({0.f, 0.f, 0.f}) {
    auto winSize = AppManager::get()->getWinSize();
    setBoundingBox(winSize);
    setPos((winSize / 2.f).toVec());
}

NS_SPECTRUM_END