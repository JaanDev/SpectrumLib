#include "Scene.hpp"

#include "AppManager.hpp"

NS_SPECTRUM_BEGIN

Scene::Scene() : Node() {
    auto winSize = AppManager::instance()->getWinSize();
    setBoundingBox(winSize);
    setPos(winSize / 2.f);
}

NS_SPECTRUM_END