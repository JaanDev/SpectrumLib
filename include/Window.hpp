#pragma once
#include "Includes.hpp"
#include "Canvas.hpp"

NS_SPECTRUM_BEGIN

class Window {
private:
    GLFWwindow* m_window;
    
    // my inner perfectionist is crying rn
    std::function<void(Window*)> m_closeCallback;
    std::function<void(Window*, Vec2f)> m_contentScaleCallback;
    std::function<void(Window*, bool)> m_focusCallback;
    std::function<void(Window*, bool)> m_iconifyCallback;
    std::function<void(Window*, bool)> m_maximizeCallback;
    std::function<void(Window*)> m_refreshCallback;
    std::function<void(Window*, Vec2i)> m_posCallback;
    std::function<void(Window*, Vec2i)> m_sizeCallback;
    std::function<void(Window*, Vec2i)> m_framebufferSizeCallback;

    static void closeCallback(GLFWwindow* win);
    static void contentScaleCallback(GLFWwindow* win, float x, float y);
    static void focusCallback(GLFWwindow* win, int focused);
    static void iconifyCallback(GLFWwindow* win, int iconified);
    static void maximizeCallback(GLFWwindow* win, int maximized);
    static void refreshCallback(GLFWwindow* win);
    static void posCallback(GLFWwindow* win, int x, int y);
    static void sizeCallback(GLFWwindow* win, int x, int y);
    static void framebufferSizeCallback(GLFWwindow* win, int width, int height);

    std::shared_ptr<Canvas> m_canvas;

public:
    // inline static std::unordered_map<GLFWwindow*, Window*> g_windows = {}; // for callbacks

    Window(std::string_view title, const Vec2i& size, const std::vector<WindowHint>& hints);
    ~Window();

    GLFWwindow* getWindow();

    // the `ratio` is the numenator and the denominator. both values of `ratio` can be GLFW_DONT_CARE (havent checked)
    void setAspectRatio(const Vec2i& ratio);

    void setAttribs(const std::vector<WindowAttrib>& attribs);
    std::vector<WindowAttrib> getAttribs();

    void setCloseCallback(std::function<void(Window*)> callback);

    Vec2f getContentScale();

    // Vec4 getWindowFrameSize(); // TODO: Create Vec4 type or use 2 Vec2f's or anything else
    
    void setContentScaleCallback(std::function<void(Window*, Vec2f)> callback);

    void setWindowFocusCallback(std::function<void(Window*, bool)> callback);

    // void setWindowIcon(...); // TODO

    // = on minimize
    void setWindowIconifyCallback(std::function<void(Window*, bool)> callback);

    void setWindowMaximizeCallback(std::function<void(Window*, bool)> callback);

    void setMonitor(GLFWmonitor* mon, const Vec2i& pos, const Vec2i& size, int refreshRate);
    GLFWmonitor* getMonitor();

    // 0 <= opacity <= 1
    void setOpacity(float opacity);
    // 0 <= opacity <= 1
    float getOpacity();

    void setPosition(const Vec2i& pos);
    Vec2i getPosition();

    void setPosCallback(std::function<void(Window*, Vec2i)> callback);

    void setRefreshCallback(std::function<void(Window*)> callback);

    void setShouldClose(bool shouldClose);
    bool shouldClose();

    void setSize(const Vec2i& size);
    Vec2i getSize();

    void setSizeCallback(std::function<void(Window*, Vec2i)> callback);

    void setFramebufferSizeCallback(std::function<void(Window*, Vec2i)> callback);

    // any vector member can be GLFW_DONT_CARE (GLFW_DONT_CARE works for the whole vector)
    void setSizeLimits(const Vec2i& min, const Vec2i& max);

    void setTitle(const std::string_view title);

    void destroyWindow();

    Vec2i getFramebufferSize();

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

    static std::shared_ptr<Window> create(std::string_view title, Vec2i size, const std::vector<WindowHint>& hints);

    std::shared_ptr<Canvas> getCanvas();
};

NS_SPECTRUM_END