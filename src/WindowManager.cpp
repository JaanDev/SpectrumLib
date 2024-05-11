#include "WindowManager.hpp"

#include <memory>
#include <stb_image.h>
#include "FileManager.hpp"
#include "AppManager.hpp"
#include "InputDispatcher.hpp"
#include "DefaultIcon.hpp"
#include "logger.hpp"

NS_SPECTRUM_BEGIN

WindowManager* WindowManager::get() {
    static auto instance = WindowManager();
    return &instance;
}

WindowManager::WindowManager()
    : m_windowHandle(nullptr), m_closeCallback(nullptr), m_filesDroppedCallback(nullptr), m_isFullscreen(false), m_isVsync(false), m_fsWinPos({0, 0}),
      m_fsWinSize({0, 0}) {}

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

    if (sizeInPixels.w / sizeInPoints.w != sizeInPixels.h / sizeInPoints.h) {
        logE("The aspect ratio between sizeInPixels and sizeInPoints must be the same!");
        return;
    }

    // initial points to pixels ratio
    m_initialPointsToPixels = sizeInPoints.w / sizeInPixels.w;
    m_initialWinSize = sizeInPoints;
    m_realPointsToPixels = m_initialPointsToPixels;
    m_winSize = sizeInPoints;

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

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    m_windowHandle = glfwCreateWindow(sizeInPixels.w, sizeInPixels.h, title.c_str(), nullptr, nullptr);
    if (!m_windowHandle) {
        logE("Failed to create a window!");
        exit(1);
    }
    glfwMakeContextCurrent(m_windowHandle);

    gladLoadGL(glfwGetProcAddress);
    logD("OpenGL Version: {}", (char*)glGetString(GL_VERSION));
    logD("GLSL Version:   {}", (char*)glGetString(GL_SHADING_LANGUAGE_VERSION));
    logD("GLAD Version:   {}", GLAD_GENERATOR_VERSION);
    logD("GLFW Version:   {}", glfwGetVersionString());
    logD("Renderer:       {}", (char*)glGetString(GL_RENDERER));
    logD("Vendor:         {}", (char*)glGetString(GL_VENDOR));

    glfwSwapInterval(m_isVsync ? 1 : 0);

    glfwSetWindowCloseCallback(m_windowHandle, [](GLFWwindow* win) {
        auto wmgr = WindowManager::get();
        if (wmgr->m_closeCallback) {
            glfwSetWindowShouldClose(wmgr->m_windowHandle, wmgr->m_closeCallback());
        }
    });

    glfwSetKeyCallback(m_windowHandle, [](GLFWwindow* window, int key, int scancode, int action, int mods) {
        InputDispatcher::get()->keyCallback(key, scancode, action, mods);
    });

    glfwSetCharCallback(m_windowHandle, [](GLFWwindow* window, unsigned int codepoint) { InputDispatcher::get()->charCallback(codepoint); });

    glfwSetDropCallback(m_windowHandle, [](GLFWwindow* window, int path_count, const char** paths) {
        auto wmgr = WindowManager::get();
        if (wmgr->m_filesDroppedCallback) {
            std::vector<std::string> files;

            for (auto i = 0; i < path_count; i++) {
                files.push_back(paths[i]);
            }

            wmgr->m_filesDroppedCallback(files);
        }
    });

    glfwSetScrollCallback(m_windowHandle, [](GLFWwindow* win, double x, double y) {
        InputDispatcher::get()->mouseScrollCallback({static_cast<float>(x), static_cast<float>(y)});
    });

    glfwSetCursorPosCallback(m_windowHandle, [](GLFWwindow* window, double xpos, double ypos) {
        InputDispatcher::get()->mousePosCallback(
            WindowManager::get()->pixelsToPointsReal(Vec2f {static_cast<float>(xpos), static_cast<float>(ypos)}));
    });

    glfwSetMouseButtonCallback(
        m_windowHandle, [](GLFWwindow* window, int button, int action, int mods) { InputDispatcher::get()->mouseBtnCallback(button, action, mods); });

    glfwSetFramebufferSizeCallback(m_windowHandle, [](GLFWwindow* window, int w, int h) {
        if (w == 0 || h == 0)
            return;

        glViewport(0, 0, w, h);

        auto wmgr = WindowManager::get();
        auto oldAspectRatio = wmgr->m_initialWinSize.w / wmgr->m_initialWinSize.h;
        auto newAspectRatio = static_cast<float>(w) / static_cast<float>(h);

        if (newAspectRatio > oldAspectRatio) {
            wmgr->m_winSize = {wmgr->m_initialWinSize.w, wmgr->m_initialWinSize.h * (oldAspectRatio / newAspectRatio)};
        } else {
            wmgr->m_winSize = {wmgr->m_initialWinSize.w * (newAspectRatio / oldAspectRatio), wmgr->m_initialWinSize.h};
        }

        wmgr->m_realPointsToPixels = wmgr->m_winSize.w / w;
    });

    setDefaultWindowIcon();

    setFullscreen(fullscreen);
}

void WindowManager::setWindowIcon(const std::string& iconPath) {
    auto fullPath = FileManager::get()->fullPathForFile(iconPath);
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

void WindowManager::enableAspectRatio(bool enable) {
    glfwSetWindowAspectRatio(m_windowHandle, enable ? m_initialWinSize.w : GLFW_DONT_CARE, enable ? m_initialWinSize.h : GLFW_DONT_CARE);
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
    m_isVsync = vsync;
    glfwSwapInterval(m_isVsync ? 1 : 0);
}

Sizei WindowManager::getWinSizeInPixels() {
    int w, h;
    glfwGetWindowSize(m_windowHandle, &w, &h);
    return {w, h};
}

void WindowManager::setWinSizeInPixels(const Sizei& size) {
    glfwSetWindowSize(m_windowHandle, size.w, size.h);
}

Vec2f WindowManager::pointsToPixels(const Vec2f& pointPos) {
    return pointPos / m_initialPointsToPixels;
}

Vec2f WindowManager::pixelsToPoints(const Vec2f& pixelPos) {
    return pixelPos * m_initialPointsToPixels;
}

Vec2f WindowManager::pointsToPixelsReal(const Vec2f& pointPos) {
    return pointPos / m_realPointsToPixels;
}

Vec2f WindowManager::pixelsToPointsReal(const Vec2f& pixelPos) {
    return pixelPos * m_realPointsToPixels;
}

Sizef WindowManager::pixelsToSize(const Sizef& pixelSize) {
    return pixelSize * m_initialPointsToPixels;
}

Sizef WindowManager::sizeToPixels(const Sizef& size) {
    return size / m_initialPointsToPixels;
}

Vec2f WindowManager::getMousePos() {
    return pixelsToPointsReal(getMousePosInPixels());
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

void WindowManager::setDefaultWindowIcon() {
    int x, y, bpp;
    auto loadedData = stbi_load_from_memory(g_defaultIconData, g_defaultIconDataSize, &x, &y, &bpp, 0);
    if (!loadedData) {
        logE("Failed to load a default window icon!");
        return;
    }

    GLFWimage img = {.width = x, .height = y, .pixels = loadedData};
    glfwSetWindowIcon(m_windowHandle, 1, &img);

    stbi_image_free(loadedData);
}

NS_SPECTRUM_END
