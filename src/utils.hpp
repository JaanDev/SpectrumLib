#pragma once

#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include <type_traits>

#define NS_SPECTRUM_BEGIN namespace spl {
#define NS_SPECTRUM_END }

#include "types.hpp"
#include "MiniFunction.hpp"

NS_SPECTRUM_BEGIN

namespace utils {
    // Col3u to RGBA
    uint32_t Col3uToInt(const Col3u& col);
    // Col3f to RGBA
    uint32_t Col3fToInt(const Col3f& col);
    // Col4u to RGBA
    uint32_t Col4uToInt(const Col4u& col);
    // Col4f to RGBA
    uint32_t Col4fToInt(const Col4f& col);

    // RGBA to Col3u
    Col3u IntToCol3u(uint32_t col);
    // RGBA to Col3f
    Col3f IntToCol3f(uint32_t col);
    // RGBA to Col4u
    Col4u IntToCol4u(uint32_t col);
    // RGBA to Col4f
    Col4f IntToCol4f(uint32_t col);

    float calcEasing(EasingType easingType, float x);

    template <typename T>
    T lerpValue(T start, T end, float t) {
        return start + (end - start) * t;
    }
} // namespace utils

NS_SPECTRUM_END