#include "Window.hpp"

NS_SPECTRUM_BEGIN

std::shared_ptr<Window> Window::create(std::string_view title, Vec2i size, const std::vector<WindowHint>& hints) {
    return std::make_shared<Window>(title, size, hints);
}

std::shared_ptr<Canvas> Window::getCanvas() {
    return m_canvas;
}

Window::Window(std::string_view title, const Vec2i& size, const std::vector<WindowHint>& hints) :
        m_framebufferSizeCallback(nullptr),
        m_closeCallback(nullptr),
        m_focusCallback(nullptr),
        m_iconifyCallback(nullptr),
        m_maximizeCallback(nullptr),
        m_posCallback(nullptr),
        m_refreshCallback(nullptr),
        m_sizeCallback(nullptr),
        m_contentScaleCallback(nullptr) {
            
    static bool initializedGL = false;
    if (!initializedGL) {
        if (!glfwInit()) {
            const char* error;
            int code = glfwGetError(&error);
            utils::logE("Failed to initialize glfw ({}; code {})", error, code);
            exit(1);
        }
    }

    for (const auto& [hint, value] : hints) {
        glfwWindowHint(static_cast<int>(hint), static_cast<int>(value));
    }

    // TODO: More params customization
    m_window = glfwCreateWindow(size.x, size.y, std::string(title).c_str(), NULL, NULL);
    if (!m_window) {
        const char* error;
        int code = glfwGetError(&error);
        utils::logE("Failed to create a window ({}; code {})", error, code);
        glfwTerminate();
        exit(1);
    }

    glfwMakeContextCurrent(m_window);

    glfwSetWindowUserPointer(m_window, this);

    if (!initializedGL) {
        glewExperimental = true;
        if (auto code = glewInit(); code != GLEW_OK) {
            utils::logE("Failed to initialize glew ({}; code {})", (const char*)glewGetErrorString(code), code);
            exit(1);
        }

        utils::logD("OpenGL version: {}", (const char*)glGetString(GL_VERSION));
        utils::logD("Renderer:       {}", (const char*)glGetString(GL_RENDERER));
        utils::logD("Vendor:         {}", (const char*)glGetString(GL_VENDOR));
        utils::logD("GLSL version:   {}", (const char*)glGetString(GL_VERSION));

        initializedGL = true;
    }

    m_canvas = Canvas::create(m_window);

    // g_windows.insert(std::make_pair(m_window, this));
}

Window::~Window() {
    // TODO: Make better window closing system
    if (glfwGetCurrentContext() == m_window) {
        utils::logD("Terminating glfw");
        glfwTerminate();
    }
}

GLFWwindow* Window::getWindow() {
    return m_window;
}

void Window::setAspectRatio(const Vec2i& ratio) {
    glfwSetWindowAspectRatio(m_window, ratio.x, ratio.y);
}

void Window::setAttribs(const std::vector<WindowAttrib>& attribs) {
    for (const auto& [attrib, value] : attribs) {
        glfwSetWindowAttrib(m_window, static_cast<int>(attrib), static_cast<int>(value));
    }
}

std::vector<WindowAttrib> Window::getAttribs() {
    std::vector<WindowAttrib> ret;

    for (const auto attrib : { WindowAttribs::AutoIconify, WindowAttribs::Decorated, WindowAttribs::Floating, WindowAttribs::FocusOnShow, WindowAttribs::Resizable }) {
        ret.push_back(std::make_pair(attrib, glfwGetWindowAttrib(m_window, static_cast<int>(attrib))));
    }
    
    return ret;
}

Vec2f Window::getContentScale() {
    Vec2f ret;
    glfwGetWindowContentScale(m_window, &ret.x, &ret.y);
    return ret;
}

void Window::setContentScaleCallback(std::function<void(Window*, Vec2f)> callback) {
    m_contentScaleCallback = callback;
    glfwSetWindowContentScaleCallback(m_window, contentScaleCallback);
}

void Window::setWindowFocusCallback(std::function<void(Window*, bool)> callback) {
    m_focusCallback = callback;
    glfwSetWindowFocusCallback(m_window, focusCallback);
}

void Window::setCloseCallback(std::function<void(Window*)> callback) {
    m_closeCallback = callback;
    glfwSetWindowCloseCallback(m_window, closeCallback);
}

void Window::setWindowIconifyCallback(std::function<void(Window*, bool)> callback) {
    m_iconifyCallback = callback;
    glfwSetWindowIconifyCallback(m_window, iconifyCallback);
}

void Window::setWindowMaximizeCallback(std::function<void(Window*, bool)> callback) {
    m_maximizeCallback = callback;
    glfwSetWindowMaximizeCallback(m_window, maximizeCallback);
}

void Window::setMonitor(GLFWmonitor* mon, const Vec2i& pos, const Vec2i& size, int refreshRate) {
    glfwSetWindowMonitor(m_window, mon, pos.x, pos.y, size.x, size.y, refreshRate);
}

GLFWmonitor* Window::getMonitor() {
    return glfwGetWindowMonitor(m_window);
}

void Window::setOpacity(float opacity) {
    glfwSetWindowOpacity(m_window, opacity);
}

float Window::getOpacity() {
    return glfwGetWindowOpacity(m_window);
}

void Window::setPosition(const Vec2i& pos) {
    glfwSetWindowPos(m_window, pos.x, pos.y);
}

Vec2i Window::getPosition() {
    Vec2i ret;
    glfwGetWindowPos(m_window, &ret.x, &ret.y);
    return ret;
}

void Window::setPosCallback(std::function<void(Window*, Vec2i)> callback) {
    m_posCallback = callback;
    glfwSetWindowPosCallback(m_window, posCallback);
}

void Window::setRefreshCallback(std::function<void(Window*)> callback) {
    m_refreshCallback = callback;
    glfwSetWindowRefreshCallback(m_window, refreshCallback);
}

void Window::setShouldClose(bool shouldClose) {
    glfwSetWindowShouldClose(m_window, shouldClose);
}

bool Window::shouldClose() {
    return glfwWindowShouldClose(m_window);
}

void Window::setSize(const Vec2i& size) {
    glfwSetWindowSize(m_window, size.x, size.y);
}

Vec2i Window::getSize() {
    Vec2i ret;
    glfwGetWindowSize(m_window, &ret.x, &ret.y);
    return ret;
}

void Window::setSizeCallback(std::function<void(Window*, Vec2i)> callback) {
    m_sizeCallback = callback;
    glfwSetWindowSizeCallback(m_window, sizeCallback);
}

void Window::setFramebufferSizeCallback(std::function<void(Window *, Vec2i)> callback) {
    m_framebufferSizeCallback = callback;
    glfwSetFramebufferSizeCallback(m_window, framebufferSizeCallback);
}

void Window::setSizeLimits(const Vec2i& min, const Vec2i& max) {
    glfwSetWindowSizeLimits(m_window, min.x, min.y, max.x, max.y);
}

void Window::setTitle(const std::string_view title) {
    glfwSetWindowTitle(m_window, std::string(title).c_str());
}

void Window::destroyWindow() {
    glfwDestroyWindow(m_window);
}

Vec2i Window::getFramebufferSize() {
    Vec2i ret;
    glfwGetFramebufferSize(m_window, &ret.x, &ret.y);
    return ret;
}

void Window::closeCallback(GLFWwindow *win) {
    // // utils::logD("closeCallback");
    // if (auto pair = Window::g_windows.find(_win); pair != Window::g_windows.end()) {
    //     // std::cout << "AAA" << std::endl;
    //     auto win = pair->second;
    //     // std::cout << "BBB" << std::hex << (void*)win << ";" << std::hex << (void*)win->m_closeCallback << std::endl;
    //     // utils::logD("{:X}; {:X}", (void*)win, (void*)win->m_closeCallback);
    //     if (win && win->m_closeCallback) win->m_closeCallback(win);
    //     // std::cout << "CCC" << std::endl;
    //     // utils::logD("1");
    //     // // if (win->m_closeCallback && *(win->m_closeCallback)) {
    //     // if (win->m_closeCallback) {
    //     //     utils::logD("2");
    //     //     // auto fn = *(win->m_closeCallback);
    //     //     utils::logD("3");
    //     //     fn(win);
    //     //     utils::logD("4");
    //     // }
    // }

    auto _win = (Window*)glfwGetWindowUserPointer(win);
    if (_win && _win->m_closeCallback) _win->m_closeCallback(_win);
}

void Window::contentScaleCallback(GLFWwindow *win, float x, float y) {
    auto _win = (Window*)glfwGetWindowUserPointer(win);
    if (_win && _win->m_contentScaleCallback) _win->m_contentScaleCallback(_win, {x, y});
}

void Window::focusCallback(GLFWwindow *win, int focused) {
    auto _win = (Window*)glfwGetWindowUserPointer(win);
    if (_win && _win->m_focusCallback) _win->m_focusCallback(_win, focused);
}

void Window::iconifyCallback(GLFWwindow *win, int iconified) {
    auto _win = (Window*)glfwGetWindowUserPointer(win);
    if (_win && _win->m_iconifyCallback) _win->m_iconifyCallback(_win, iconified);
}

void Window::maximizeCallback(GLFWwindow *win, int maximized) {
    auto _win = (Window*)glfwGetWindowUserPointer(win);
    if (_win && _win->m_maximizeCallback) _win->m_maximizeCallback(_win, maximized);
}

void Window::refreshCallback(GLFWwindow *win) {
    auto _win = (Window*)glfwGetWindowUserPointer(win);
    if (_win && _win->m_refreshCallback) _win->m_refreshCallback(_win);
}

void Window::posCallback(GLFWwindow *win, int x, int y) {
    auto _win = (Window*)glfwGetWindowUserPointer(win);
    if (_win && _win->m_posCallback) _win->m_posCallback(_win, Vec2i {x, y});
}

void Window::sizeCallback(GLFWwindow *win, int x, int y) {
    auto _win = (Window*)glfwGetWindowUserPointer(win);
    if (_win && _win->m_sizeCallback) _win->m_sizeCallback(_win, Vec2i {x, y});
}

void Window::framebufferSizeCallback(GLFWwindow *win, int width, int height) {
    auto _win = (Window*)glfwGetWindowUserPointer(win);
    if (_win && _win->m_sizeCallback) _win->m_sizeCallback(_win, Vec2i {width, height});
}

void Window::iconify() {
    glfwIconifyWindow(m_window);
}

void Window::restore() {
    glfwRestoreWindow(m_window);
}

void Window::maximize() {
    glfwMaximizeWindow(m_window);
}

void Window::show() {
    glfwShowWindow(m_window);
}

void Window::hide() {
    glfwHideWindow(m_window);
}

void Window::focus() {
    glfwFocusWindow(m_window);
}

void Window::requestAttention() {
    glfwRequestWindowAttention(m_window);
}

void Window::swapBuffers() {
    glfwSwapBuffers(m_window);
}

NS_SPECTRUM_END