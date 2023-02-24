#pragma once
#include <iostream>
#include <ostream>
#include <format>
#include <functional>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#define NS_SPECTRUM_BEGIN namespace spectrum {
#define NS_SPECTRUM_END }

NS_SPECTRUM_BEGIN

namespace utils {
    template <typename... Args>
    void logE(Args... args) {
        std::cout << "[Spectrum] ERROR: " << std::format(args...) << std::endl;
    }

    template <typename... Args>
    void logD(Args... args) {
        std::cout << "[Spectrum] DEBUG: " << std::format(args...) << std::endl;
    }

    template <typename... Args>
    void logW(Args... args) {
        std::cout << "[Spectrum] WARNING: " << std::format(args...) << std::endl;
    }

    // leave `message` empty for the default "GLFW Error"
    inline void handleGLError(std::string_view message, std::function<void()> fn) {
        const char* desc;
        if (auto code = glfwGetError(&desc); code != GLFW_NO_ERROR) {
            logW("{}: {} with code {}", message == "" ? "GLFW Error" : message, desc, code);
            if (fn) fn();
        }
    }
}

NS_SPECTRUM_END

#include "Vector.hpp"
#include "GLUtils.hpp"