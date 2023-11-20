#pragma once
#include <functional>
#include <string>
#include "utils.hpp"

NS_SPECTRUM_BEGIN

class WindowManager {
  public:
    static WindowManager* instance();
    WindowManager();
    ~WindowManager();

    void createWindow(const Sizei& sizeInPixels, const Sizef& sizeInPoints, const std::string& title, bool fullscreen,
                      WindowFlags windowFlags = WindowFlags::Default);

    void setWindowIcon(const std::string& iconPath);

    // bool() => возвращает true если окно закрывать, false если не закрывать
    inline void setOnCloseCallback(std::function<bool()> callback) { m_closeCallback = callback; }

    void setFullscreen(bool fullscreen);
    inline bool getFullscreen() const { return m_isFullscreen; }

    void setVsync(bool vsync);
    inline bool getVsync() const { return m_isVsync; }

    Sizei getWinSizeInPixels();
    void setWinSizeInPixels(const Sizei& size);

    inline GLFWwindow* getGLFWWindow() const { return m_windowHandle; }

    Vec2f getMousePos();
    Vec2f getMousePosInPixels();

    Vec2i getWindowPos();
    void setWindowPos(const Vec2i& pos);

    void setWindowTitle(const std::string& title);

    inline void setFilesDroppedCallback(std::function<void(std::vector<std::string>)> callback) {
        m_filesDroppedCallback = callback;
    }

    // all 3 are for this frame
    Vec2f getMouseWheelDelta();
    Vec2f getMouseDelta();
    Vec2i getMouseDeltaInPixels();

  private:
    void setDefaultWindowIcon();

    GLFWwindow* m_windowHandle;
    std::function<bool()> m_closeCallback;
    std::function<void(std::vector<std::string>)> m_filesDroppedCallback;
    Sizei m_fsWinSize; // for fullscreen
    Vec2i m_fsWinPos;  // for fullscreen
    bool m_isFullscreen;
    bool m_isVsync;
};

NS_SPECTRUM_END