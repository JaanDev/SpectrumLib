#pragma once
#include "Includes.hpp"

NS_SPECTRUM_BEGIN

class Window {
private:
    GLFWwindow* m_window;
    
    // my inner perfectionist is crying rn
    std::function<void(Window*)> m_closeCallback;
    std::function<void(Window*, Vec2)> m_contentScaleCallback;
    std::function<void(Window*, bool)> m_focusCallback;
    std::function<void(Window*, bool)> m_iconifyCallback;
    std::function<void(Window*, bool)> m_maximizeCallback;
    std::function<void(Window*)> m_refreshCallback;
    std::function<void(Window*, Vec2)> m_posCallback;
    std::function<void(Window*, Vec2)> m_sizeCallback;
    std::function<void(Window*, Vec2)> m_framebufferSizeCallback;

    static void closeCallback(GLFWwindow* win);
    static void contentScaleCallback(GLFWwindow* win, float x, float y);
    static void focusCallback(GLFWwindow* win, int focused);
    static void iconifyCallback(GLFWwindow* win, int iconified);
    static void maximizeCallback(GLFWwindow* win, int maximized);
    static void refreshCallback(GLFWwindow* win);
    static void posCallback(GLFWwindow* win, int x, int y);
    static void sizeCallback(GLFWwindow* win, int x, int y);
    static void framebufferSizeCallback(GLFWwindow* win, int width, int height);

public:
    // inline static std::unordered_map<GLFWwindow*, Window*> g_windows = {}; // for callbacks

    Window(std::string_view title, Vec2 size, const std::vector<WindowHint>& hints);
    ~Window();

    GLFWwindow* getWindow();

    // the `ratio` is the numenator and the denominator. both values of `ratio` can be GLFW_DONT_CARE (havent checked)
    void setAspectRatio(const Vec2& ratio);

    void setAttribs(const std::vector<WindowAttrib>& attribs);
    std::vector<WindowAttrib> getAttribs();

    void setCloseCallback(std::function<void(Window*)> callback);

    Vec2 getContentScale();

    // Vec4 getWindowFrameSize(); // TODO: Create Vec4 type or use 2 Vec2's or anything else
    
    void setContentScaleCallback(std::function<void(Window*, Vec2)> callback);

    void setWindowFocusCallback(std::function<void(Window*, bool)> callback);

    // void setWindowIcon(...); // TODO

    // = on minimize
    void setWindowIconifyCallback(std::function<void(Window*, bool)> callback);

    void setWindowMaximizeCallback(std::function<void(Window*, bool)> callback);

    void setMonitor(GLFWmonitor* mon, const Vec2& pos, const Vec2& size, int refreshRate);
    GLFWmonitor* getMonitor();

    // 0 <= opacity <= 1
    void setOpacity(float opacity);
    // 0 <= opacity <= 1
    float getOpacity();

    void setPosition(const Vec2& pos);
    Vec2 getPosition();

    void setPosCallback(std::function<void(Window*, Vec2)> callback);

    void setRefreshCallback(std::function<void(Window*)> callback);

    void setShouldClose(bool shouldClose);
    bool shouldClose();

    void setSize(const Vec2& size);
    Vec2 getSize();

    void setSizeCallback(std::function<void(Window*, Vec2)> callback);

    void setFramebufferSizeCallback(std::function<void(Window*, Vec2)> callback);

    // any vector member can be GLFW_DONT_CARE (GLFW_DONT_CARE works for the whole vector)
    void setSizeLimits(const Vec2& min, const Vec2& max);

    void setTitle(const std::string_view title);

    void destroyWindow();

    Vec2 getFramebufferSize();

    // minimize
    void iconify();

    // restore if was iconified (minimized) or maximized
    void restore();

    void maximize();

    // makes visible if was hidden
    void show();

    // makes hidden if was shown
    void hide();

    void focus();

    void requestAttention();

    void swapBuffers();

    static std::shared_ptr<Window> create(std::string_view title, Vec2 size, const std::vector<WindowHint>& hints);
};

NS_SPECTRUM_END