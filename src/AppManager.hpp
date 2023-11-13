#pragma once
#include <memory>
#include <string>
#include <vector>
#include "utils.hpp"

NS_SPECTRUM_BEGIN

class Scene;

class AppManager {
  public:
    static AppManager* instance();
    AppManager();

    void run();
    void pause();
    void resume();
    void end();

    double getTime();

    void setContentScale(float scale);
    inline float getContentScale() const { return m_contentScale; }

    // in points
    inline const Sizef& getWinSize() const { return m_winSize; }

    void setCursorVisible(bool visible);
    inline bool getCursorVisible() const { return m_isCursorVisible; }

    void setCursorLocked(bool locked);
    inline bool getCursorLocked() const { return m_isCursorLocked; }

    void openURL(const std::string& url);

    inline float getTimeScale() const;
    void setTimeScale(float ts);

    std::shared_ptr<Scene> getCurrentScene();
    void pushScene(std::shared_ptr<Scene> scene);
    void replaceScene(std::shared_ptr<Scene> scene);
    // -1 => go 1 scene back, 1 => go 1 scene forward etc
    void goToScene(int step);

    float getRealFPS();

    std::string getClipboardText();
    void setClipboardText(const std::string& text);

    Vec2f pointsToPixels(const Vec2f& pointPos);
    Vec2f pixelsToPoints(const Vec2f& pixelPos);

    Sizef sizeToPixels(const Sizef& size);
    Sizef pixelsToSize(const Sizef& pixelSize);

  private:
    float m_timeScale;
    Sizef m_winSize;        // in points
    Vec2f m_pointsToPixels; // points to pixels ratio
    float m_contentScale;
    std::vector<std::shared_ptr<Scene>> m_scenes;
    int m_currentScene;
    bool m_isRunning;
    bool m_isCursorVisible;
    bool m_isCursorLocked;
};

NS_SPECTRUM_END