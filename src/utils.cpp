#include "utils.hpp"

#include "math.h"
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
        const float PI = 3.14159265358979323846;
        const float c1 = 1.70158;
        const float c3 = c1 + 1;
        const float c2 = c1 * 1.525;
        const float c4 = (2 * PI) / 3;
        const float c5 = (2 * PI) / 4.5;

        switch (easingType) {
        case EasingType::Linear:
            return x;
        case EasingType::EaseInQuad:
            return x * x;
        case EasingType::EaseOutQuad:
            return 1 - (1 - x) * (1 - x);
        case EasingType::EaseInOutQuad:
            return x < 0.5 ? 2 * x * x : 1 - pow(-2 * x + 2, 2) / 2;
        case EasingType::EaseInCubic:
            return x * x * x;
        case EasingType::EaseOutCubic:
            return 1 - pow(1 - x, 3);
        case EasingType::EaseInOutCubic:
            return x < 0.5 ? 4 * x * x * x : 1 - pow(-2 * x + 2, 3) / 2;
        case EasingType::EaseInQuart:
            return x * x * x * x;
        case EasingType::EaseOutQuart:
            return 1 - pow(1 - x, 4);
        case EasingType::EaseInOutQuart:
            return x < 0.5 ? 8 * x * x * x * x : 1 - pow(-2 * x + 2, 4) / 2;
        case EasingType::EaseInQuint:
            return x * x * x * x * x;
        case EasingType::EaseOutQuint:
            return 1 - pow(1 - x, 5);
        case EasingType::EaseInOutQuint:
            return x < 0.5 ? 16 * x * x * x * x * x : 1 - pow(-2 * x + 2, 5) / 2;
        case EasingType::EaseInSine:
            return 1 - cos((x * PI) / 2);
        case EasingType::EaseOutSine:
            return sin((x * PI) / 2);
        case EasingType::EaseInOutSine:
            return -(cos(PI * x) - 1) / 2;
        case EasingType::EaseInExpo:
            return x == 0 ? 0 : pow(2, 10 * x - 10);
        case EasingType::EaseOutExpo:
            return x == 1 ? 1 : 1 - pow(2, -10 * x);
        case EasingType::EaseInOutExpo:
            return x == 0 ? 0 : x == 1 ? 1 : x < 0.5 ? pow(2, 20 * x - 10) / 2 : (2 - pow(2, -20 * x + 10)) / 2;
        case EasingType::EaseInCirc:
            return 1 - sqrt(1 - pow(x, 2));
        case EasingType::EaseOutCirc:
            return sqrt(1 - pow(x - 1, 2));
        case EasingType::EaseInOutCirc:
            return x < 0.5 ? (1 - sqrt(1 - pow(2 * x, 2))) / 2 : (sqrt(1 - pow(-2 * x + 2, 2)) + 1) / 2;
        case EasingType::EaseInBack:
            return c3 * x * x * x - c1 * x * x;
        case EasingType::EaseOutBack:
            return 1 + c3 * pow(x - 1, 3) + c1 * pow(x - 1, 2);
        case EasingType::EaseInOutBack:
            return x < 0.5 ? (pow(2 * x, 2) * ((c2 + 1) * 2 * x - c2)) / 2
                           : (pow(2 * x - 2, 2) * ((c2 + 1) * (x * 2 - 2) + c2) + 2) / 2;
        case EasingType::EaseInElastic:
            return x == 0 ? 0 : x == 1 ? 1 : -pow(2, 10 * x - 10) * sin((x * 10 - 10.75) * c4);
        case EasingType::EaseOutElastic:
            return x == 0 ? 0 : x == 1 ? 1 : pow(2, -10 * x) * sin((x * 10 - 0.75) * c4) + 1;
        case EasingType::EaseInOutElastic:
            return x == 0    ? 0
                   : x == 1  ? 1
                   : x < 0.5 ? -(pow(2, 20 * x - 10) * sin((20 * x - 11.125) * c5)) / 2
                             : (pow(2, -20 * x + 10) * sin((20 * x - 11.125) * c5)) / 2 + 1;
        case EasingType::EaseInBounce:
            return 1 - calcEasing(EasingType::EaseOutBounce, 1 - x);
        case EasingType::EaseOutBounce: {
            if (x < 1.f / 2.75f) {
                return x * x * 7.5625f;
            } else if (x < 2.f / 2.75f) {
                x -= 1.5f / 2.75f;
                return x * x * 7.5625f + 0.75f;
            } else if (x < 2.5f / 2.75f) {
                x -= 2.25f / 2.75f;
                return x * x * 7.5625f + 0.9375f;
            } else {
                x -= 2.625f / 2.75f;
                return x * x * 7.5625f + 0.984375f;
            }
        } break;
        case EasingType::EaseInOutBounce:
            return x < 0.5 ? (1 - calcEasing(EasingType::EaseOutBounce, 1 - 2 * x)) / 2
                           : (1 + calcEasing(EasingType::EaseOutBounce, 2 * x - 1)) / 2;
        default:
            logW("Unknown easing type!");
            return x;
            break;
        }
    }
} // namespace utils

NS_SPECTRUM_END