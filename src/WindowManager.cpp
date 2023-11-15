#include "WindowManager.hpp"

#include <memory>
#include <stb_image.h>
#include "FileManager.hpp"
#include "AppManager.hpp"
#include "logger.hpp"

NS_SPECTRUM_BEGIN

WindowManager* WindowManager::instance() {
    static auto instance = std::make_unique<WindowManager>();
    return instance.get();
}

WindowManager::WindowManager()
    : m_winSize({0, 0}), m_windowHandle(nullptr), m_closeCallback(nullptr), m_filesDroppedCallback(nullptr),
      m_isFullscreen(false), m_isVsync(false), m_fsWinPos({0, 0}), m_fsWinSize({0, 0}) {}

WindowManager::~WindowManager() {
    glfwDestroyWindow(m_windowHandle);
    glfwTerminate();
}

void WindowManager::createWindow(const Sizei& sizeInPixels, const Sizef& sizeInPoints, const std::string& title, bool fullscreen,
                                 WindowFlags windowFlags) {
    static bool createdWindow = false;
    if (createdWindow) {
        logW("WindowManager::createWindow has already been called, not creating a window");
        return;
    }
    createdWindow = true;

    glfwSetErrorCallback([](int error, const char* desc) { logE("GLFW Error: {} (code {})", desc, error); });

    if (!glfwInit()) {
        logE("Failed to initialize GLFW!");
        exit(1);
    }

#define APPLY_WIN_HINT(name, glfwName) glfwWindowHint(glfwName, static_cast<unsigned int>(windowFlags & name) != 0);

    APPLY_WIN_HINT(WindowFlags::Resizable, GLFW_RESIZABLE)
    APPLY_WIN_HINT(WindowFlags::Visible, GLFW_VISIBLE)
    APPLY_WIN_HINT(WindowFlags::Decorated, GLFW_DECORATED)
    APPLY_WIN_HINT(WindowFlags::Focused, GLFW_FOCUSED)
    APPLY_WIN_HINT(WindowFlags::AutoIconify, GLFW_AUTO_ICONIFY)
    APPLY_WIN_HINT(WindowFlags::Floating, GLFW_FLOATING)
    APPLY_WIN_HINT(WindowFlags::Maximized, GLFW_MAXIMIZED)
    APPLY_WIN_HINT(WindowFlags::CenterCursor, GLFW_CENTER_CURSOR)
    APPLY_WIN_HINT(WindowFlags::TransparentFramebuffer, GLFW_TRANSPARENT_FRAMEBUFFER)
    APPLY_WIN_HINT(WindowFlags::FocusOnShow, GLFW_FOCUS_ON_SHOW)
    APPLY_WIN_HINT(WindowFlags::ScaleToMonitor, GLFW_SCALE_TO_MONITOR)

#undef APPLY_WIN_HINT

    m_windowHandle = glfwCreateWindow(sizeInPixels.w, sizeInPixels.h, title.c_str(), nullptr, nullptr);
    if (!m_windowHandle) {
        logE("Failed to create a window!");
        exit(1);
    }
    setFullscreen(fullscreen);
    glfwSetWindowAspectRatio(m_windowHandle, sizeInPixels.w, sizeInPixels.h);

    glfwMakeContextCurrent(m_windowHandle);

    gladLoadGL(glfwGetProcAddress);
    logD("OpenGL Version: {}", (char*)glGetString(GL_VERSION));
    logD("GLSL Version:   {}", (char*)glGetString(GL_SHADING_LANGUAGE_VERSION));
    logD("GLAD Version:   {}", GLAD_GENERATOR_VERSION);
    logD("Renderer:       {}", (char*)glGetString(GL_RENDERER));
    logD("Vendor:         {}", (char*)glGetString(GL_VENDOR));

    glfwSwapInterval(m_isVsync);

    glfwSetWindowSizeCallback(m_windowHandle, [](GLFWwindow* win, int w, int h) {
        logD("win size {}x{}", w, h);
        glViewport(0, 0, w, h);
    });

    glfwSetWindowCloseCallback(m_windowHandle, [](GLFWwindow* win) { logD("close"); });

    glfwSetKeyCallback(m_windowHandle, [](GLFWwindow* window, int key, int scancode, int action, int mods) {
        logD("key {} {} {} {}", key, scancode, action, mods);
    });

    glfwSetCharCallback(m_windowHandle, [](GLFWwindow* window, unsigned int codepoint) { logD("char {}", codepoint); });

    glfwSetDropCallback(m_windowHandle, [](GLFWwindow* window, int path_count, const char** paths) {
        for (auto i = 0; i < path_count; i++) {
            logD("drop file {}", paths[i]);
        }
    });

    glfwSetScrollCallback(m_windowHandle, [](GLFWwindow* win, double x, double y) { logD("scroll {} {}", x, y); });

    glfwSetCursorPosCallback(m_windowHandle, [](GLFWwindow* window, double xpos, double ypos) {
        // logD("cursor pos {} {}", xpos, ypos);
    });

    AppManager::instance()->m_winSize = sizeInPoints;
    AppManager::instance()->m_pointsToPixels = sizeInPoints / sizeInPixels.to<float>();
}

void WindowManager::setWindowIcon(const std::string& iconPath) {
    auto fullPath = FileManager::instance()->fullPathForFile(iconPath);
    int w, h, bpp;
    auto data = stbi_load(fullPath.string().c_str(), &w, &h, &bpp, 0);
    if (!data) {
        logE("Failed to load an image for the window icon {}", fullPath.string());
        return;
    }

    auto img = GLFWimage {.width = w, .height = h, .pixels = data};
    glfwSetWindowIcon(m_windowHandle, 1, &img);
    stbi_image_free(data);
}

void WindowManager::setFullscreen(bool fullscreen) {
    if (m_isFullscreen == fullscreen)
        return;

    m_isFullscreen = fullscreen;

    if (fullscreen) {
        m_fsWinPos = getWindowPos();
        m_fsWinSize = getWinSizeInPixels();

        auto mon = glfwGetPrimaryMonitor();
        auto mode = glfwGetVideoMode(mon);
        glfwSetWindowMonitor(m_windowHandle, mon, 0, 0, mode->width, mode->height, mode->refreshRate);
    } else {
        glfwSetWindowMonitor(m_windowHandle, nullptr, m_fsWinPos.x, m_fsWinPos.y, m_fsWinSize.w, m_fsWinSize.h, 0);
    }
}

void WindowManager::setVsync(bool vsync) {
    if (m_isVsync == vsync)
        return;

    m_isVsync = vsync;

    glfwSwapInterval(m_isVsync);
}

void WindowManager::setWinSizeInPixels(const Sizei& size) {
    glfwSetWindowSize(m_windowHandle, size.w, size.h);
}

Vec2f WindowManager::getMousePos() {
    return Vec2f();
}

Vec2f WindowManager::getMousePosInPixels() {
    double x, y;
    glfwGetCursorPos(m_windowHandle, &x, &y);
    return {static_cast<float>(x), static_cast<float>(y)};
}

Vec2i WindowManager::getWindowPos() {
    int x, y;
    glfwGetWindowPos(m_windowHandle, &x, &y);
    return {x, y};
}

void WindowManager::setWindowPos(const Vec2i& pos) {
    glfwSetWindowPos(m_windowHandle, pos.x, pos.y);
}

void WindowManager::setWindowTitle(const std::string& title) {
    glfwSetWindowTitle(m_windowHandle, title.c_str());
}

Vec2f WindowManager::getMouseWheelDelta() {
    return Vec2f();
}

Vec2f WindowManager::getMouseDelta() {
    return Vec2f();
}

Vec2i WindowManager::getMouseDeltaInPixels() {
    return Vec2i();
}

NS_SPECTRUM_END
