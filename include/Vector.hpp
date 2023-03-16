#pragma once
#include "Includes.hpp"

NS_SPECTRUM_BEGIN

struct Vec2 {
    float x;
    float y;

    auto operator<=>(const Vec2& other) const = default;
    
    constexpr Vec2  operator+(const Vec2& other) { return { this->x + other.x, this->y + other.y }; }
    constexpr Vec2  operator-(const Vec2& other) { return { this->x - other.x, this->y - other.y }; }
    constexpr Vec2& operator+=(const Vec2& other) { *this = *this + other; return *this; }
    constexpr Vec2& operator-=(const Vec2& other) { *this = *this - other; return *this; }

    constexpr Vec2  operator*(const Vec2& other) { return { this->x * other.x, this->y * other.y }; }
    constexpr Vec2  operator/(const Vec2& other) { return { this->x / other.x, this->y / other.y }; }
    constexpr Vec2& operator*=(const Vec2& other) { *this = *this * other; return *this; }
    constexpr Vec2& operator/=(const Vec2& other) { *this = *this / other; return *this; }

    constexpr Vec2  operator*(const float other) { return { this->x * other, this->y * other }; }
    constexpr Vec2  operator/(const float other) { return { this->x / other, this->y / other }; }
    constexpr Vec2& operator*=(const float other) { *this = *this * other; return *this; }
    constexpr Vec2& operator/=(const float other) { *this = *this / other; return *this; }
};

inline std::ostream& operator<<(std::ostream& os, const Vec2& other) {
    os << "{" << other.x << "; " << other.y << "}";
    return os;
}

// struct Vec3f {
//     float x;
//     float y;
//     float z;

//     auto operator<=>(const Vec3f& other) const = default;
    
//     constexpr Vec3f  operator+(const Vec3f& other) { return { this->x + other.x, this->y + other.y, this->z + other.z }; }
//     constexpr Vec3f  operator-(const Vec3f& other) { return { this->x - other.x, this->y - other.y, this->z - other.z }; }
//     constexpr Vec3f& operator+=(const Vec3f& other) { *this = *this + other; return *this; }
//     constexpr Vec3f& operator-=(const Vec3f& other) { *this = *this - other; return *this; }

//     constexpr Vec3f  operator*(const Vec3f& other) { return { this->x * other.x, this->y * other.y, this->y * other.y }; }
//     constexpr Vec3f  operator/(const Vec3f& other) { return { this->x / other.x, this->y / other.y, this->y / other.y }; }
//     constexpr Vec3f& operator*=(const Vec3f& other) { *this = *this * other; return *this; }
//     constexpr Vec3f& operator/=(const Vec3f& other) { *this = *this / other; return *this; }

//     constexpr Vec3f  operator*(const float other) { return { this->x * other, this->y * other, this->z * other }; }
//     constexpr Vec3f  operator/(const float other) { return { this->x / other, this->y / other, this->z / other }; }
//     constexpr Vec3f& operator*=(const float other) { *this = *this * other; return *this; }
//     constexpr Vec3f& operator/=(const float other) { *this = *this / other; return *this; }
// };

// inline std::ostream& operator<<(std::ostream& os, const Vec3f& other) {
//     os << "{" << other.x << "; " << other.y << other.z << "}";
//     return os;
// }

template <typename T = float>
struct Vec3 {
    T x;
    T y;
    T z;

    auto operator<=>(const Vec3& other) const = default;
    
    constexpr Vec3  operator+(const Vec3& other) { return { this->x + other.x, this->y + other.y, this->z + other.z }; }
    constexpr Vec3  operator-(const Vec3& other) { return { this->x - other.x, this->y - other.y, this->z - other.z }; }
    constexpr Vec3& operator+=(const Vec3& other) { *this = *this + other; return *this; }
    constexpr Vec3& operator-=(const Vec3& other) { *this = *this - other; return *this; }

    constexpr Vec3  operator*(const Vec3& other) { return { this->x * other.x, this->y * other.y, this->y * other.y }; }
    constexpr Vec3  operator/(const Vec3& other) { return { this->x / other.x, this->y / other.y, this->y / other.y }; }
    constexpr Vec3& operator*=(const Vec3& other) { *this = *this * other; return *this; }
    constexpr Vec3& operator/=(const Vec3& other) { *this = *this / other; return *this; }

    constexpr Vec3  operator*(const T other) { return { this->x * other, this->y * other, this->z * other }; }
    constexpr Vec3  operator/(const T other) { return { this->x / other, this->y / other, this->z / other }; }
    constexpr Vec3& operator*=(const T other) { *this = *this * other; return *this; }
    constexpr Vec3& operator/=(const T other) { *this = *this / other; return *this; }
};

template <typename T>
inline std::ostream& operator<<(std::ostream& os, const Vec3<T> other) {
    os << "{" << other.x << "; " << other.y << "; " << other.z << "}";
    return os;
}

template <typename T = float>
struct Vec4 {
    T x;
    T y;
    T z;
    T w;

    auto operator<=>(const Vec4& other) const = default;
    
    constexpr Vec4  operator+(const Vec4& other) { return { this->x + other.x, this->y + other.y, this->z + other.z, this->w + other.w }; }
    constexpr Vec4  operator-(const Vec4& other) { return { this->x - other.x, this->y - other.y, this->z - other.z, this->w - other.w }; }
    constexpr Vec4& operator+=(const Vec4& other) { *this = *this + other; return *this; }
    constexpr Vec4& operator-=(const Vec4& other) { *this = *this - other; return *this; }

    constexpr Vec4  operator*(const Vec4& other) { return { this->x * other.x, this->y * other.y, this->y * other.y, this->w * other.w }; }
    constexpr Vec4  operator/(const Vec4& other) { return { this->x / other.x, this->y / other.y, this->y / other.y, this->w / other.w }; }
    constexpr Vec4& operator*=(const Vec4& other) { *this = *this * other; return *this; }
    constexpr Vec4& operator/=(const Vec4& other) { *this = *this / other; return *this; }

    constexpr Vec4  operator*(const T other) { return { this->x * other, this->y * other, this->z * other, this->w * other }; }
    constexpr Vec4  operator/(const T other) { return { this->x / other, this->y / other, this->z / other, this->w / other }; }
    constexpr Vec4& operator*=(const T other) { *this = *this * other; return *this; }
    constexpr Vec4& operator/=(const T other) { *this = *this / other; return *this; }
};

template <typename T>
inline std::ostream& operator<<(std::ostream& os, const Vec4<T> other) {
    os << "{" << other.x << "; " << other.y << "; " << other.z << "; " << other.w << "}";
    return os;
}

NS_SPECTRUM_END