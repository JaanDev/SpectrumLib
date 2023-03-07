#pragma once
#include "fmt/core.h"
#include <iostream>
#include <ostream>
// #include <format>
#include <fmt/core.h>
#include <fmt/color.h>
#include <utility>
#include <vector>
#include <functional>
#include <map>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#define NS_SPECTRUM_BEGIN namespace spectrum {
#define NS_SPECTRUM_END }

NS_SPECTRUM_BEGIN

namespace utils {
    template <typename Fmt, typename... Args>
    void logE(Fmt fmt, Args... args) {
        // std::cout << "[Spectrum] \033[1;31mERROR: " << fmt::format(args...) << "\033[0m" << std::endl; // bold bright red
        // fmt::println(fg(fmt::color::red) | fmt::emphasis::bold, args...);
        std::cout << "[Spectrum] " << fmt::format(fg(fmt::terminal_color::red) | fmt::emphasis::bold, std::string("Error: ") + fmt, args...) << std::endl;
        // fmt::println(args...);
        // std::cout << "[Spectrum] \033[1;31mERROR: " << std::format(args...) << "\033[0m" << std::endl; // bold bright red
    }

    template <typename Fmt, typename... Args>
    void logD(Fmt fmt, Args... args) {
        // std::cout << "[Spectrum] \033[0;30mDEBUG: " << std::format(args...) << "\033[0m" << std::endl; // gray
        // std::cout << "[Spectrum] DEBUG: " << fmt::format(args...) << std::endl;
        std::cout << "[Spectrum] " << fmt::format(fg(fmt::terminal_color::bright_white), std::string("Debug: ") + fmt, args...) << std::endl;
    }

    template <typename Fmt, typename... Args>
    void logW(Fmt fmt, Args... args) {
        // std::cout << "[Spectrum] \033[0;33mWARNING: " << fmt::format(args...) << "\033[0m" << std::endl; // yellow
        std::cout << "[Spectrum] " << fmt::format(fg(fmt::terminal_color::bright_yellow), std::string("Warning: ") + fmt, args...) << std::endl;
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