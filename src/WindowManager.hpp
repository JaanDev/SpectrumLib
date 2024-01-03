#pragma once
#include <functional>
#include <string>
#include "utils.hpp"

NS_SPECTRUM_BEGIN

class SPL_API WindowManager {
  public:
    static WindowManager* get();
    WindowManager();
    ~WindowManager();

    void createWindow(const Sizei& sizeInPixels, const Sizef& sizeInPoints, const std::string& title, bool fullscreen,
                      WindowFlags windowFlags = WindowFlags::Default);

    void setWindowIcon(const std::string& iconPath);

    // bool() => возвращает true если окно закрывать, false если не закрывать
    inline void setOnCloseCallback(MiniFunction<bool()> callback) { m_closeCallback = callback; }

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

    inline void setFilesDroppedCallback(MiniFunction<void(std::vector<std::string>)> callback) {
        m_filesDroppedCallback = callback;
    }

  private:
    void setDefaultWindowIcon();

    GLFWwindow* m_windowHandle;
    MiniFunction<bool()> m_closeCallback;
    MiniFunction<void(std::vector<std::string>)> m_filesDroppedCallback;
    Sizei m_fsWinSize; // for fullscreen
    Vec2i m_fsWinPos;  // for fullscreen
    Vec2f m_curPointsToPixels;
    bool m_isFullscreen;
    bool m_isVsync;
};

NS_SPECTRUM_END