#include "AppManager.hpp"

NS_SPECTRUM_BEGIN

AppManager* AppManager::instance() {
    static auto instance = std::make_shared<AppManager>();
    return instance.get();
}

AppManager::AppManager()
    : m_winSize({0, 0}), m_pointsToPixels({0.f, 0.f}), m_contentScale(1.f), m_scenes({}), m_currentScene(0), m_isRunning(false),
      m_isCursorVisible(true), m_isCursorLocked(false) {}

void AppManager::run() {}

void AppManager::update() {}

void AppManager::pause() {}

void AppManager::resume() {}

void AppManager::end() {}

double AppManager::getTime() {
    return glfwGetTime();
}

void AppManager::setContentScale(float scale) {}

void AppManager::setCursorVisible(bool visible) {}

void AppManager::setCursorLocked(bool locked) {}

void AppManager::openURL(const std::string& url) {}

std::shared_ptr<Scene> AppManager::getCurrentScene() {
    return std::shared_ptr<Scene>();
}

void AppManager::pushScene(std::shared_ptr<Scene> scene) {}

void AppManager::replaceScene(std::shared_ptr<Scene> scene) {}

void AppManager::goToScene(int step) {}

float AppManager::getRealFPS() {
    return 0.0f;
}

std::string AppManager::getClipboardText() {
    return std::string();
}

void AppManager::setClipboardText(const std::string& text) {}

Vec2f AppManager::pointsToPixels(const Vec2f& pointPos) {
    return Vec2f();
}

Vec2f AppManager::pixelsToPoints(const Vec2f& pixelPos) {
    return Vec2f();
}

NS_SPECTRUM_END
