#pragma once
#include "Includes.hpp"

NS_SPECTRUM_BEGIN

class Window {
private:
    std::string m_title;
    Vec2 m_size;
    GLFWwindow* m_window;

public:
    Window(std::string_view title, Vec2 size) : m_title(std::move(title)), m_size(std::move(size)) {
        static bool initializedGL = false;

        if (!initializedGL) {
            if (!glfwInit()) {
                const char* error;
                int code = glfwGetError(&error);

                utils::logE("Failed to initialize glfw ({}; code {})", error, code);
                exit(1);
            }
        }

        // TODO: More params customization
        m_window = glfwCreateWindow((int)m_size.x, (int)m_size.y, m_title.c_str(), NULL, NULL);
        utils::handleGLError("Failed to create a window", nullptr);

        glfwMakeContextCurrent(m_window);

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
    }

    ~Window() {
        // TODO: Make better window closing system
        if (glfwGetCurrentContext() == m_window) {
            utils::logD("Terminating glfw");
            glfwTerminate();
        }
    }

    void setTitle(const std::string& str);

    static std::shared_ptr<Window> create(std::string_view title, Vec2 size);
};

NS_SPECTRUM_END