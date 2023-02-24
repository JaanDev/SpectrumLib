#pragma once
#include "Includes.hpp"

struct Vec2 {
    float x;
    float y;

    auto operator<=>(const Vec2& other) const = default;
    
    constexpr Vec2 operator+(const Vec2& other) { return { this->x + other.x, this->y + other.y }; }
    constexpr Vec2 operator-(const Vec2& other) { return { this->x - other.x, this->y - other.y }; }
    constexpr Vec2& operator+=(const Vec2& other) { *this = *this + other; return *this; }
    constexpr Vec2& operator-=(const Vec2& other) { *this = *this - other; return *this; }

    constexpr Vec2 operator*(const Vec2& other) { return { this->x * other.x, this->y * other.y }; }
    constexpr Vec2 operator/(const Vec2& other) { return { this->x / other.x, this->y / other.y }; }
    constexpr Vec2 operator*=(const Vec2& other) { *this = *this * other; return *this; }
    constexpr Vec2 operator/=(const Vec2& other) { *this = *this / other; return *this; }

    constexpr Vec2 operator*(const float other) { return { this->x * other, this->y * other }; }
    constexpr Vec2 operator/(const float other) { return { this->x / other, this->y / other }; }
    constexpr Vec2 operator*=(const float other) { *this = *this * other; return *this; }
    constexpr Vec2 operator/=(const float other) { *this = *this / other; return *this; }
};

inline std::ostream& operator<<(std::ostream& os, const Vec2& other) {
    os << "{" << other.x << "; " << other.y << "}";
    return os;
}