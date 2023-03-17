#include <Canvas.hpp>

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

void Canvas::line(const Vec2f &start, const Vec2f &end, const Col4 &col) {
    // auto normStart = utils::normalize(start);
    // auto normEnd = utils::normalize(end);

    glBegin(GL_LINES);
        // glVertex2f(normStart.x, normStart.y);
        // glVertex2f(normEnd.x, normEnd.y);
        glColor4ub(col.x, col.y, col.z, col.w);
        glVertex2i((int)start.x, (int)start.y);
        glVertex2i((int)end.x, (int)end.y);
    glEnd();
}

NS_SPECTRUM_END