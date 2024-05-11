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

    void createWindow(const Vec2i& Vec2inPixels, const Vec2f& Vec2inPoints, const std::string& title, bool fullscreen,
                      WindowFlags windowFlags = WindowFlags::Default);

    // bool() => возвращает true если окно закрывать, false если не закрывать
    inline void setOnCloseCallback(MiniFunction<bool()> callback) { m_closeCallback = callback; }
    inline void setFilesDroppedCallback(MiniFunction<void(std::vector<std::string>)> callback) { m_filesDroppedCallback = callback; }

    void setFullscreen(bool fullscreen);
    inline bool getFullscreen() const { return m_isFullscreen; }

    void setVsync(bool vsync);
    inline bool getVsync() const { return m_isVsync; }

    inline GLFWwindow* getGLFWWindow() const { return m_windowHandle; }

    Vec2f getMousePos();
    Vec2f getMousePosInPixels();

    Vec2i getWindowPos();
    void setWindowPos(const Vec2i& pos);

    void setWindowTitle(const std::string& title);
    void setWindowIcon(const std::string& iconPath);

    void enableAspectRatio(bool enable);

    Vec2i getWinVec2inPixels();
    void setWinVec2inPixels(const Vec2i& size);

    Vec2f pointsToPixelsReal(const Vec2f& pointPos);
    Vec2f pixelsToPointsReal(const Vec2f& pixelPos);
    Vec2f pointsToPixels(const Vec2f& pointPos);
    Vec2f pixelsToPoints(const Vec2f& pixelPos);

    Vec2f sizeToPixels(const Vec2f& size);
    Vec2f pixelsToSize(const Vec2f& pixelSize);

    inline float getPointsToPixelsRatio() const { return m_initialPointsToPixels; }
    inline float getPointsToPixelsRatioReal() const { return m_realPointsToPixels; }

    // in points
    inline const Vec2f& getWinSize() const { return m_winSize; }

  private:
    void setDefaultWindowIcon();

    GLFWwindow* m_windowHandle;
    MiniFunction<bool()> m_closeCallback;
    MiniFunction<void(std::vector<std::string>)> m_filesDroppedCallback;
    Vec2i m_fsWinSize;      // for fullscreen
    Vec2i m_fsWinPos;       // for fullscreen
    Vec2f m_initialWinSize; // in points
  public:
    float m_initialPointsToPixels; // for texture loading etc, otherwise the textures would have different size in different sized windows :P

  private:
    float m_realPointsToPixels;
    Vec2f m_winSize; // in points
    bool m_isFullscreen;
    bool m_isVsync;
};

NS_SPECTRUM_END