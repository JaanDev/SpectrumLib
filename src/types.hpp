#pragma once
#include "utils.hpp"

NS_SPECTRUM_BEGIN

template <typename T>
struct Vec2 {
    T x;
    T y;

    Vec2<T> operator+(const Vec2<T>& other) { return {x + other.x, y + other.y}; }
    Vec2<T> operator-(const Vec2<T>& other) { return {x - other.x, y - other.y}; }
    Vec2<T> operator*(const Vec2<T>& other) { return {x * other.x, y * other.y}; }
    Vec2<T> operator/(const Vec2<T>& other) { return {x / other.x, y / other.y}; }
    Vec2<T> operator*(T other) { return {x * other, y * other}; }
    Vec2<T> operator/(T other) { return {x / other, y / other}; }

    void operator+=(const Vec2<T>& other) { *this = *this + other; }
    void operator-=(const Vec2<T>& other) { *this = *this - other; }
    void operator*=(const Vec2<T>& other) { *this = *this * other; }
    void operator/=(const Vec2<T>& other) { *this = *this / other; }
    void operator*=(T other) { *this = *this * other; }
    void operator/=(T other) { *this = *this / other; }

    float distance(const Vec2<T>& other) { return sqrtf(powf(other.x - x, 2) + powf(other.y - y)); }
};

template <typename T>
struct Size {
    T w;
    T h;

    Size<T> operator*(T other) { return {w * other, h * other}; }
    Size<T> operator/(T other) { return {w / other, h / other}; }
    void operator*=(T other) { *this = *this * other; }
    void operator/=(T other) { *this = *this / other; }

    T getArea() { return w * h; }
};

template <typename T>
struct Rect {
    T x;
    T y;
    T w;
    T h;

    bool doesIntersect(const Rect<T>& other) {
        return x < other.x + other.w && x + w > other.x && y > other.y + other.h && y + h < other.y;
    }
};

template <typename T>
struct Col3 {
    T r;
    T g;
    T b;
};

template <typename T>
struct Col4 {
    T r;
    T g;
    T b;
    T a;
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

NS_SPECTRUM_END