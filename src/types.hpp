#pragma once
#include "utils.hpp"

NS_SPECTRUM_BEGIN

template <typename T>
struct Size;

template <typename T>
struct Vec2 {
    T x;
    T y;

    template <typename T2>
    Vec2<T> operator+(const Vec2<T2>& other) const {
        return {x + other.x, y + other.y};
    }
    template <typename T2>
    Vec2<T> operator-(const Vec2<T2>& other) const {
        return {x - other.x, y - other.y};
    }
    template <typename T2>
    Vec2<T> operator*(const Vec2<T2>& other) const {
        return {x * other.x, y * other.y};
    }
    template <typename T2>
    Vec2<T> operator/(const Vec2<T2>& other) const {
        return {x / other.x, y / other.y};
    }
    template <typename T2>
    Vec2<T> operator*(T2 other) const {
        return {x * other, y * other};
    }
    template <typename T2>
    Vec2<T> operator/(T2 other) const {
        return {x / other, y / other};
    }

    template <typename T2>
    void operator+=(const Vec2<T2>& other) {
        *this = *this + other;
    }
    template <typename T2>
    void operator-=(const Vec2<T2>& other) {
        *this = *this - other;
    }
    template <typename T2>
    void operator*=(const Vec2<T2>& other) {
        *this = *this * other;
    }
    template <typename T2>
    void operator/=(const Vec2<T2>& other) {
        *this = *this / other;
    }
    template <typename T2>
    void operator*=(T2 other) {
        *this = *this * other;
    }
    template <typename T2>
    void operator/=(T2 other) {
        *this = *this / other;
    }

    float distance(const Vec2<T>& other) const { return sqrtf(powf(other.x - x, 2) + powf(other.y - y, 2)); }

    operator Size<T>() const { return {x, y}; }

    template <typename T2>
    inline Vec2<T2> to() const {
        return {static_cast<T2>(x), static_cast<T2>(y)};
    }
};

template <typename T>
struct Size {
    T w;
    T h;

    template <typename T2>
    Size<T> operator*(T2 other) const {
        return {static_cast<T>(w * other), static_cast<T>(h * other)};
    }
    template <typename T2>
    Size<T> operator/(T2 other) const {
        return {static_cast<T>(w / other), static_cast<T>(h / other)};
    }
    template <typename T2>
    Size<T> operator*(Size<T2> other) const {
        return {static_cast<T>(w * other.w), static_cast<T>(h * other.h)};
    }
    template <typename T2>
    Size<T> operator/(Size<T2> other) const {
        return {static_cast<T>(w / other.w), static_cast<T>(h / other.h)};
    }
    template <typename T2>
    Size<T> operator*(Vec2<T2> other) const {
        return {static_cast<T>(w * other.x), static_cast<T>(h * other.y)};
    }
    template <typename T2>
    Size<T> operator/(Vec2<T2> other) const {
        return {static_cast<T>(w / other.x), static_cast<T>(h / other.y)};
    }
    void operator*=(T other) { *this = *this * other; }
    void operator/=(T other) { *this = *this / other; }

    T getArea() const { return w * h; }

    operator Vec2<T>() const { return {w, h}; }

    template <typename T2>
    inline Size<T2> to() const {
        return {static_cast<T2>(w), static_cast<T2>(h)};
    }
};

template <typename T>
struct Rect {
    T x;
    T y;
    T w;
    T h;

    bool doesIntersect(const Rect<T>& other) const {
        return x < other.x + other.w && x + w > other.x && y > other.y + other.h && y + h < other.y;
    }
};

template <typename T>
struct Col3 {
    T r;
    T g;
    T b;

    Col3<T> operator+(const Col3<T>& other) {
        return {static_cast<T>(r + other.r), static_cast<T>(g + other.g), static_cast<T>(b + other.b)};
    }
    Col3<T> operator-(const Col3<T>& other) {
        return {static_cast<T>(r - other.r), static_cast<T>(g - other.g), static_cast<T>(b - other.b)};
    }
    Col3<T> operator*(const Col3<T>& other) {
        return {static_cast<T>(r * other.r), static_cast<T>(g * other.g), static_cast<T>(b * other.b)};
    }
    Col3<T> operator/(const Col3<T>& other) {
        return {static_cast<T>(r / other.r), static_cast<T>(g / other.g), static_cast<T>(b / other.b)};
    }
    template <typename T2>
    Col3<T> operator*(T2 other) {
        return {static_cast<T>(r * other), static_cast<T>(g * other), static_cast<T>(b * other)};
    }
    template <typename T2>
    Col3<T> operator/(T2 other) {
        return {static_cast<T>(r / other), static_cast<T>(g / other), static_cast<T>(b / other)};
    }

    void operator+=(const Col3<T>& other) { *this = *this + other; }
    void operator-=(const Col3<T>& other) { *this = *this - other; }
    void operator*=(const Col3<T>& other) { *this = *this * other; }
    void operator/=(const Col3<T>& other) { *this = *this / other; }
    void operator*=(T other) { *this = *this * other; }
    void operator/=(T other) { *this = *this / other; }
};

template <typename T>
struct Col4 {
    T r;
    T g;
    T b;
    T a;

    Col4<T> operator+(const Col4<T>& other) { return {r + other.r, g + other.g, b + other.b, a + other.a}; }
    Col4<T> operator-(const Col4<T>& other) { return {r - other.r, g - other.g, b - other.b, a - other.a}; }
    Col4<T> operator*(const Col4<T>& other) { return {r * other.r, g * other.g, b * other.b, a * other.a}; }
    Col4<T> operator/(const Col4<T>& other) { return {r / other.r, g / other.g, b / other.b, a / other.a}; }
    Col4<T> operator*(T other) { return {r * other, g * other, b * other, a * other}; }
    Col4<T> operator/(T other) { return {r / other, g / other, b / other, a / other}; }

    void operator+=(const Col4<T>& other) { *this = *this + other; }
    void operator-=(const Col4<T>& other) { *this = *this - other; }
    void operator*=(const Col4<T>& other) { *this = *this * other; }
    void operator/=(const Col4<T>& other) { *this = *this / other; }
    void operator*=(T other) { *this = *this * other; }
    void operator/=(T other) { *this = *this / other; }
};

using Sizef = Size<float>;
using Sizei = Size<int>;

using Rectf = Rect<float>;
using Recti = Rect<int>;

using Vec2f = Vec2<float>;
using Vec2i = Vec2<int>;

using Col3f = Col3<float>;
using Col3u = Col3<unsigned char>;

using Col4f = Col4<float>;
using Col4u = Col4<unsigned char>;

// https://github.com/ai/easings.net/blob/master/src/easings/easingsFunctions.ts
enum class EasingType {
    Linear,
    EaseInQuad,
    EaseOutQuad,
    EaseInOutQuad,
    EaseInCubic,
    EaseOutCubic,
    EaseInOutCubic,
    EaseInQuart,
    EaseOutQuart,
    EaseInOutQuart,
    EaseInQuint,
    EaseOutQuint,
    EaseInOutQuint,
    EaseInSine,
    EaseOutSine,
    EaseInOutSine,
    EaseInExpo,
    EaseOutExpo,
    EaseInOutExpo,
    EaseInCirc,
    EaseOutCirc,
    EaseInOutCirc,
    EaseInBack,
    EaseOutBack,
    EaseInOutBack,
    EaseInElastic,
    EaseOutElastic,
    EaseInOutElastic,
    EaseInBounce,
    EaseOutBounce,
    EaseInOutBounce
};

enum class KeyEventType {
    KeyDown,
    KeyUp
};

enum class MouseEventType {
    MouseHold,
    MouseRelease,
    MouseMove,
    MouseEnterArea,
    MouseLeaveArea
};

enum class ModKeys {
    None = 0,
    Shift = 1 << 0,
    Control = 1 << 1,
    Alt = 1 << 2,
    Super = 1 << 3,
    CapsLock = 1 << 4, // if the GLFW_LOCK_KEY_MODS input mode is set.
    NumLock = 1 << 5   // if the GLFW_LOCK_KEY_MODS input mode is set.
};

enum class WindowFlags {
    // no flags
    None = 0,
    // whether the windowed mode window will be resizable by the user
    Resizable = 1 << 0,
    // whether the windowed mode window will be initially visible
    Visible = 1 << 1,
    // whether the windowed mode window will have window decorations such as a border, a close widget, etc.
    Decorated = 1 << 2,
    // whether the windowed mode window will be given input focus when created
    Focused = 1 << 3,
    // whether the full screen window will automatically iconify and restore the previous video mode on input focus loss
    AutoIconify = 1 << 4,
    // whether the windowed mode window will be floating above other regular windows, also called topmost or always-on-top.
    Floating = 1 << 5,
    // whether the windowed mode window will be maximized when created
    Maximized = 1 << 6,
    // whether the cursor should be centered over newly created full screen windows
    CenterCursor = 1 << 7,
    // whether the window framebuffer will be transparent. If enabled and supported by the system, the window framebuffer alpha
    // channel will be used to combine the framebuffer with the background. This does not affect window decorations.
    TransparentFramebuffer = 1 << 8,
    // whether the window will be given input focus when glfwShowWindow is called
    FocusOnShow = 1 << 9,
    // whether the window content area should be resized based on the monitor content scale of any monitor it is placed on
    ScaleToMonitor = 1 << 10,
    Default = Visible | Decorated | Focused | AutoIconify | CenterCursor | FocusOnShow
};

inline WindowFlags operator&(WindowFlags a, WindowFlags b) {
    return static_cast<WindowFlags>(static_cast<unsigned int>(a) & static_cast<unsigned int>(b));
}
inline WindowFlags operator|(WindowFlags a, WindowFlags b) {
    return static_cast<WindowFlags>(static_cast<unsigned int>(a) | static_cast<unsigned int>(b));
}
inline WindowFlags operator^(WindowFlags a, WindowFlags b) {
    return static_cast<WindowFlags>(static_cast<unsigned int>(a) ^ static_cast<unsigned int>(b));
}

enum class TextAlignmentH : uint8_t {
    Left,
    Center,
    Right
};

enum class TextAlignmentV : uint8_t {
    Top,
    Center,
    Bottom
};

enum class ShapeType : uint8_t {
    None,
    Ellipse,
    Polygon,
    Line
};

enum class FillType : uint8_t {
    None,
    SolidColor,
    Gradient,
    Texture
};

NS_SPECTRUM_END