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
    void fill(const Col4& col);
    
    // draw a line
    void line(const Vec2f& start, const Vec2f& end, const Col4& col);
};

NS_SPECTRUM_END