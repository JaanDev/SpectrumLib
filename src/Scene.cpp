#include "Scene.hpp"

#include "AppManager.hpp"

NS_SPECTRUM_BEGIN

Scene::Scene() : Node(), m_color({ 0, 0, 0 }) {
    auto winSize = AppManager::instance()->getWinSize();
    setBoundingBox(winSize);
    setPos(winSize / 2.f);
}

void Scene::setColor(Col3f color){
    this->m_color = color;
}

Col3f Scene::getColor(){
    return this->m_color;
}

NS_SPECTRUM_END