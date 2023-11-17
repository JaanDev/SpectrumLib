#include "utils.hpp"

#include "logger.hpp"

NS_SPECTRUM_BEGIN

namespace utils {
    uint32_t Col3uToInt(const Col3u& col) {
        return *(uint32_t*)&col | 0x00'00'00'FFu; // convert to int and make the last byte equal to 255
    }

    uint32_t Col3fToInt(const Col3f& col) {
        return Col3uToInt(
            {static_cast<uint8_t>(col.r * 255.f), static_cast<uint8_t>(col.g * 255.f), static_cast<uint8_t>(col.b * 255.f)});
    }

    uint32_t Col4uToInt(const Col4u& col) {
        return *(uint32_t*)&col;
    }

    uint32_t Col4fToInt(const Col4f& col) {
        return Col4uToInt({static_cast<uint8_t>(col.r * 255.f), static_cast<uint8_t>(col.g * 255.f),
                           static_cast<uint8_t>(col.b * 255.f), static_cast<uint8_t>(col.a * 255.f)});
    }

    Col3u IntToCol3u(uint32_t col) {
        return *(Col3u*)&col;
    }

    Col3f IntToCol3f(uint32_t col) {
        auto col3u = IntToCol3u(col);
        return {col3u.r / 255.f, col3u.g / 255.f, col3u.b / 255.f};
    }

    Col4u IntToCol4u(uint32_t col) {
        return *(Col4u*)&col;
    }

    Col4f IntToCol4f(uint32_t col) {
        auto col4u = IntToCol4u(col);
        return {col4u.r / 255.f, col4u.g / 255.f, col4u.b / 255.f, col4u.a / 255.f};
    }

    float calcEasing(EasingType easingType, float x) {
        // https://github.com/ai/easings.net/blob/master/src/easings/easingsFunctions.ts
        // logW("Calculating easing TODO");
        return x; // linear for now
    }
} // namespace utils

NS_SPECTRUM_END