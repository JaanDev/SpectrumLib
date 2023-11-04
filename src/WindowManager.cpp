#include "WindowManager.hpp"
#include <memory>

NS_SPECTRUM_BEGIN

WindowManager* WindowManager::instance() {
    static auto instance = std::make_shared<WindowManager>();
    return instance.get();
}

void WindowManager::createWindow(const Sizei& sizeInPixels, const Sizef& sizeInPoints, const std::string& title, bool fullscreen,
                                 WindowFlags windowFlags) {}

void WindowManager::setWindowIcon(const std::string& iconPath) {}

void WindowManager::setOnCloseCallback(std::function<bool()> callback) {}

void WindowManager::setFullscreen(bool fullscreen) {}

void WindowManager::setVsync(bool vsync) {}

void WindowManager::setTargetFrameTime(float frameTime) {}

void WindowManager::setWinSizeInPixels(const Sizei& size) {}

Vec2f WindowManager::getMousePos() {
    return Vec2f();
}

Vec2i WindowManager::getMousePosInPixels() {
    return Vec2i();
}

Vec2i WindowManager::getWindowPos() {
    return Vec2i();
}

void WindowManager::setWindowPos(const Vec2i& pos) {}

void WindowManager::setWindowTitle(const std::string& title) {}

void WindowManager::setFilesDroppedCallback(std::function<void(std::vector<std::string>)> callback) {}

Vec2f WindowManager::getMouseWheelDelta() {
    return Vec2f();
}

Vec2f WindowManager::getMouseDelta() {
    return Vec2f();
}

Vec2i WindowManager::getMouseDeltaInPixels() {
    return Vec2i();
}

WindowManager::WindowManager()
    : m_winSize({0, 0}), m_targetFrameTime(1.f / 60.f), m_windowHandle(nullptr), m_closeCallback(nullptr),
      m_filesDroppedCallback(nullptr), m_isFullscreen(false), m_isVsync(false) {}

NS_SPECTRUM_END
