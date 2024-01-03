#pragma once
#include <memory>
#include <string>
#include <stack>
#include <vector>
#include "utils.hpp"
#include "WindowManager.hpp"
#include "Scene.hpp"

NS_SPECTRUM_BEGIN

class SPL_API AppManager {
    friend class WindowManager;

  public:
    static AppManager* get();
    AppManager();

    void run();
    void pause();
    void resume();
    void end();

    double getTime();
    inline float getDeltaTime() const { return m_deltaTime; }

    void setContentScale(float scale);
    inline float getContentScale() const { return m_contentScale; }

    // frameTime = 1.0 / fps;
    inline void setTargetFrameTime(float frameTime) { m_targetFrameTime = frameTime; }
    inline double getTargetFrameTime() const { return m_targetFrameTime; }

    // in points
    inline const Sizef& getWinSize() const { return m_winSize; }

    void setCursorVisible(bool visible);
    inline bool getCursorVisible() const { return m_isCursorVisible; }

    void setCursorLocked(bool locked);
    inline bool getCursorLocked() const { return m_isCursorLocked; }

    void openURL(const std::string& url);

    inline float getTimeScale() const { return m_timeScale; }
    void setTimeScale(float ts);

    std::shared_ptr<Scene> getCurrentScene();
    void pushScene(std::shared_ptr<Scene> scene);
    void replaceScene(std::shared_ptr<Scene> scene);
    // -1 => go 1 scene back, 1 => go 1 scene forward etc
    void goToScene(int step);

    inline int getRealFPS() const { return m_fps; }

    std::string getClipboardText();
    void setClipboardText(const std::string& text);

    Vec2f pointsToPixels(const Vec2f& pointPos);
    Vec2f pixelsToPoints(const Vec2f& pixelPos);

    Sizef sizeToPixels(const Sizef& size);
    Sizef pixelsToSize(const Sizef& pixelSize);

    inline const Vec2f& getPointsToPixelsRatio() const { return m_pointsToPixels; }

    const glm::mat4& getMatrix() const;

  private:
    double m_targetFrameTime;
    float m_timeScale;
    int m_fps;
    float m_deltaTime;
    Sizef m_winSize;        // in points
    Vec2f m_pointsToPixels; // points to pixels ratio
    float m_contentScale;
    std::vector<std::shared_ptr<Scene>> m_scenes;
    int m_currentScene;
    Scene* m_curScene; // for speed
    std::stack<glm::mat4> m_matrixStack;
    bool m_isRunning;
    bool m_isCursorVisible;
    bool m_isCursorLocked;
};

NS_SPECTRUM_END