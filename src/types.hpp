#pragma once
#include "utils.hpp"

NS_SPECTRUM_BEGIN

template <typename T>
struct Vec2 {
    static_assert(std::is_arithmetic_v<T>, "Unsupported type for Vec2");

    union {
        T x;
        T w;
    };

    union {
        T y;
        T h;
    };

    Vec2<T> operator+(const Vec2<T>& other) const { return {x + other.x, y + other.y}; }
    Vec2<T> operator-(const Vec2<T>& other) const { return {x - other.x, y - other.y}; }
    Vec2<T> operator*(const Vec2<T>& other) const { return {x * other.x, y * other.y}; }
    Vec2<T> operator/(const Vec2<T>& other) const { return {x / other.x, y / other.y}; }
    Vec2<T> operator*(T other) const { return {x * other, y * other}; }
    Vec2<T> operator/(T other) const { return {x / other, y / other}; }
    void operator+=(const Vec2<T>& other) { *this = *this + other; }
    void operator-=(const Vec2<T>& other) { *this = *this - other; }
    void operator*=(const Vec2<T>& other) { *this = *this * other; }
    void operator/=(const Vec2<T>& other) { *this = *this / other; }
    void operator*=(T other) { *this = *this * other; }
    void operator/=(T other) { *this = *this / other; }

    template <typename N>
    inline Vec2<N> toType() const {
        return {static_cast<N>(x), static_cast<N>(y)};
    }
};

template <typename T>
struct Rect {
    static_assert(std::is_arithmetic_v<T>, "Unsupported type for Rect");

    T x;
    T y;
    T w;
    T h;

    bool doesIntersect(const Rect<T>& other) const { return x < other.x + other.w && x + w > other.x && y > other.y + other.h && y + h < other.y; }

    bool contains(const Vec2<T>& other) const { return other.x >= x && other.x <= x + w && other.y >= y && other.y <= y + h; }

    template <typename T2>
    inline Rect<T2> to() const {
        return {static_cast<T2>(x), static_cast<T2>(y), static_cast<T2>(w), static_cast<T2>(h)};
    }
};

template <typename T>
struct Col3 {
    static_assert(std::is_arithmetic_v<T>, "Unsupported type for Col3");

    T r;
    T g;
    T b;

    Col3<T> operator+(const Col3<T>& other) { return {static_cast<T>(r + other.r), static_cast<T>(g + other.g), static_cast<T>(b + other.b)}; }
    Col3<T> operator-(const Col3<T>& other) { return {static_cast<T>(r - other.r), static_cast<T>(g - other.g), static_cast<T>(b - other.b)}; }
    Col3<T> operator*(const Col3<T>& other) { return {static_cast<T>(r * other.r), static_cast<T>(g * other.g), static_cast<T>(b * other.b)}; }
    Col3<T> operator/(const Col3<T>& other) { return {static_cast<T>(r / other.r), static_cast<T>(g / other.g), static_cast<T>(b / other.b)}; }
    Col3<T> operator*(T other) { return {static_cast<T>(r * other), static_cast<T>(g * other), static_cast<T>(b * other)}; }
    Col3<T> operator/(T other) { return {static_cast<T>(r / other), static_cast<T>(g / other), static_cast<T>(b / other)}; }
    void operator+=(const Col3<T>& other) { *this = *this + other; }
    void operator-=(const Col3<T>& other) { *this = *this - other; }
    void operator*=(const Col3<T>& other) { *this = *this * other; }
    void operator/=(const Col3<T>& other) { *this = *this / other; }
    void operator*=(T other) { *this = *this * other; }
    void operator/=(T other) { *this = *this / other; }
};

template <typename T>
struct Col4 {
    static_assert(std::is_arithmetic_v<T>, "Unsupported type for Col4");

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

enum class MouseEventType {
    MouseMove,
    MouseEnterArea,
    MouseLeaveArea
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

enum class TextAlignment : uint8_t {
    Left,
    Center,
    Right
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