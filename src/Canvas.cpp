#include "Canvas.hpp"

NS_SPECTRUM_BEGIN

Canvas::Canvas(GLFWwindow *win) : m_window(win) {
    //
}

std::shared_ptr<Canvas> Canvas::create(GLFWwindow *win) {
    return std::make_shared<Canvas>(win);
}

void Canvas::fill(const Col4& col) {
    glClearColor(col.x / 255.f, col.y / 255.f, col.z / 255.f, col.w / 255.f);
}

void Canvas::line(const Vec2i &start, const Vec2i &end, const Col4 &col) {
    glBegin(GL_LINES);
        glColor4ub(col.x, col.y, col.z, col.w);
        glVertex2i(start.x, start.y);
        glVertex2i(end.x, end.y);
    glEnd();
}

NS_SPECTRUM_END