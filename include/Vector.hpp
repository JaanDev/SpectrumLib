#pragma once
#include "Includes.hpp"

struct Vec2 {
    float x;
    float y;

    auto operator<=>(const Vec2& other) const = default;
    
    Vec2 operator+(const Vec2& other) { return { this->x + other.x, this->y + other.y }; }
    Vec2 operator-(const Vec2& other) { return { this->x - other.x, this->y - other.y }; }
    Vec2& operator+=(const Vec2& other) { *this = *this + other; return *this; }
    Vec2& operator-=(const Vec2& other) { *this = *this - other; return *this; }

    Vec2 operator*(const Vec2& other) { return { this->x * other.x, this->y * other.y }; }
    Vec2 operator/(const Vec2& other) { return { this->x / other.x, this->y / other.y }; }
    Vec2 operator*=(const Vec2& other) { *this = *this * other; return *this; }
    Vec2 operator/=(const Vec2& other) { *this = *this / other; return *this; }

    Vec2 operator*(const float other) { return { this->x * other, this->y * other }; }
    Vec2 operator/(const float other) { return { this->x / other, this->y / other }; }
    Vec2 operator*=(const float other) { *this = *this * other; return *this; }
    Vec2 operator/=(const float other) { *this = *this / other; return *this; }
};

inline std::ostream& operator<<(std::ostream& os, const Vec2& other) {
    os << "{" << other.x << "; " << other.y << "}";
    return os;
}