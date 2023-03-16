#pragma once
#include "Includes.hpp"

NS_SPECTRUM_BEGIN

class Canvas {
private:
    GLFWwindow* m_window;

public:
    Canvas(GLFWwindow* win);
    static std::shared_ptr<Canvas> create(GLFWwindow* win);

    // fill screen with color
    void fill(const Vec4<uint8_t>& col);
};

NS_SPECTRUM_END