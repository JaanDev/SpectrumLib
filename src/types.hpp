#pragma once

template <typename T>
struct Vec2 {
    T x;
    T y;
};

template <typename T>
struct Size {
    T w;
    T h;
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

using Vec2f = Vec2<float>;
using Vec2i = Vec2<int>;

using Col3f = Col3<float>;
using Col3u = Col3<unsigned char>;

using Col4f = Col4<float>;
using Col4u = Col4<unsigned char>;