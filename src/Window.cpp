#include "Window.hpp"

#include "logger.hpp"

NS_SPECTRUM_BEGIN

Window::Window(const std::string& title, const Sizei& size) : m_window(nullptr) {
    initialize();

    m_window = glfwCreateWindow(size.w, size.h, title.c_str(), nullptr, nullptr);
    if (!m_window) {
        logE("Failed to create a GLFW window!");
        exit(1);
    }

    glfwMakeContextCurrent(m_window);

    auto glVer = gladLoadGL(glfwGetProcAddress);
    logD("OpenGL Version: {}", (char*)glGetString(GL_VERSION));
    logD("GLSL Version:   {}", (char*)glGetString(GL_SHADING_LANGUAGE_VERSION));
    logD("GLAD Version:   {}", GLAD_GENERATOR_VERSION);
    logD("Renderer:       {}", (char*)glGetString(GL_RENDERER));
    logD("Vendor:         {}", (char*)glGetString(GL_VENDOR));
}

Window::~Window() {
    glfwDestroyWindow(m_window);

    shutdown();
}

NS_SPECTRUM_END