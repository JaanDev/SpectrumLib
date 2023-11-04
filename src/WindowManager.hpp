#pragma once
#include <functional>
#include <string>
#include "utils.hpp"
#include "types.hpp"

NS_SPECTRUM_BEGIN

class WindowManager {
  public:
    static WindowManager* instance();
    WindowManager();

    void createWindow(const Sizei& sizeInPixels, const Sizef& sizeInPoints, const std::string& title, bool fullscreen,
                      WindowFlags windowFlags = WindowFlags::Default);

    void setWindowIcon(const std::string& iconPath);

    // bool() => возвращает true если окно закрывать, false если не закрывать
    void setOnCloseCallback(std::function<bool()> callback);

    void setFullscreen(bool fullscreen);
    inline bool getFullscreen() const { return m_isFullscreen; }

    void setVsync(bool vsync);
    inline bool getVsync() const { return m_isVsync; }

    // frameTime = 1.0 / fps;
    void setTargetFrameTime(float frameTime);
    inline float getTargetFrameTime() const { return m_targetFrameTime; }

    inline const Sizei& getWinSizeInPixels() const { return m_winSize; }
    void setWinSizeInPixels(const Sizei& size);

    inline GLFWwindow* getGLFWWindow() const { return m_windowHandle; }

    Vec2f getMousePos();
    Vec2i getMousePosInPixels();

    Vec2i getWindowPos();
    void setWindowPos(const Vec2i& pos);

    void setWindowTitle(const std::string& title);

    void setFilesDroppedCallback(std::function<void(std::vector<std::string>)> callback);

    // all 3 are for this frame
    Vec2f getMouseWheelDelta();
    Vec2f getMouseDelta();
    Vec2i getMouseDeltaInPixels();

  private:
    Sizei m_winSize; // in pixels
    float m_targetFrameTime;
    GLFWwindow* m_windowHandle;
    std::function<bool()> m_closeCallback;
    std::function<void(std::vector<std::string>)> m_filesDroppedCallback;
    bool m_isFullscreen;
    bool m_isVsync;
};

NS_SPECTRUM_END