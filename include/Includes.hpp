#pragma once
#include <iostream>
#include <ostream>
#include <format>
#include <vector>
#include <functional>
#include <map>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#define NS_SPECTRUM_BEGIN namespace spectrum {
#define NS_SPECTRUM_END }

NS_SPECTRUM_BEGIN

namespace utils {
    template <typename... Args>
    void logE(Args... args) {
        std::cout << "[Spectrum] \033[1;31mERROR: " << std::format(args...) << "\033[0m" << std::endl; // bold bright red
    }

    template <typename... Args>
    void logD(Args... args) {
        // std::cout << "[Spectrum] \033[0;30mDEBUG: " << std::format(args...) << "\033[0m" << std::endl; // gray
        std::cout << "[Spectrum] DEBUG: " << std::format(args...) << std::endl;
    }

    template <typename... Args>
    void logW(Args... args) {
        std::cout << "[Spectrum] \033[0;33mWARNING: " << std::format(args...) << "\033[0m" << std::endl; // yellow
    }

    // leave `message` empty for the default "GLFW Error"
    inline void handleGLError(std::string_view message = "GLFW Error") {
        const char* desc;
        if (auto code = glfwGetError(&desc); code != GLFW_NO_ERROR) {
            logW("{}: {} with code {}", message, desc, code);
        }
    }
}

NS_SPECTRUM_END

#include "Vector.hpp"
#include "GLUtils.hpp"
#include "Enums.hpp"

using WindowAttrib = std::pair<WindowAttribs, bool>;
using WindowHint = std::pair<WindowHints, bool>;