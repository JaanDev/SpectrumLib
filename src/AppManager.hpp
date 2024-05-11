#pragma once
#include <memory>
#include <string>
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

    // frameTime = 1.0 / fps;
    inline void setTargetFrameTime(float frameTime) { m_targetFrameTime = frameTime; }
    inline double getTargetFrameTime() const { return m_targetFrameTime; }

    void setCursorVisible(bool visible);
    inline bool getCursorVisible() const { return m_isCursorVisible; }

    void setCursorLocked(bool locked);
    inline bool getCursorLocked() const { return m_isCursorLocked; }

    void openURL(const std::string& url);

    inline float getTimeScale() const { return m_timeScale; }
    inline void setTimeScale(float ts) { m_timeScale = ts; }

    inline Scene* getCurrentScene() { return m_curScene; }
    void pushScene(std::shared_ptr<Scene> scene);
    void replaceScene(std::shared_ptr<Scene> scene);
    // -1 => go 1 scene back, 1 => go 1 scene forward etc
    void goToScene(int step);

    inline int getRealFPS() const { return m_fps; }

    std::string getClipboardText();
    void setClipboardText(const std::string& text);

    // internal
    inline const glm::mat4& getCurMtx() const { return m_currentMatrix; }

    inline const Vec2f& getWinSize() const { return WindowManager::get()->getWinSize(); }

  private:
    float m_targetFrameTime;
    float m_timeScale;
    int m_fps;
    float m_deltaTime;
    std::vector<std::shared_ptr<Scene>> m_scenes;
    int m_currentScene;
    Scene* m_curScene; // for speed
    glm::mat4 m_currentMatrix;
    bool m_isRunning;
    bool m_isCursorVisible;
    bool m_isCursorLocked;
};

NS_SPECTRUM_END