#pragma once

#include <glad/gl.h>
#include <GLFW/glfw3.h>

#define NS_SPECTRUM_BEGIN namespace spl {
#define NS_SPECTRUM_END }

NS_SPECTRUM_BEGIN

namespace utils {
    void initialize();
    void shutdown();
} // namespace utils

NS_SPECTRUM_END