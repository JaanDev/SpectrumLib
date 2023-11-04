#pragma once

#include <glad/gl.h>
#include <GLFW/glfw3.h>

#define NS_SPECTRUM_BEGIN namespace spl {
#define NS_SPECTRUM_END }

#include "types.hpp"

NS_SPECTRUM_BEGIN

namespace utils {
    uint32_t ColToInt(const Col3u& col);
    uint32_t ColToInt(const Col3f& col);
    uint32_t ColToInt(const Col4u& col);
    uint32_t ColToInt(const Col4f& col);

    Col3u IntToCol3u(uint32_t col);
    Col3f IntToCol3f(uint32_t col);
    Col4u IntToCol4u(uint32_t col);
    Col4f IntToCol4f(uint32_t col);

    float calcEasing(EasingType easingType, float x);

    template <typename T>
    T lerpValue(T start, T end, float t) {
        return start + (end - start) * t;
    }
} // namespace utils

NS_SPECTRUM_END