#include <Canvas.hpp>

NS_SPECTRUM_BEGIN

Canvas::Canvas(GLFWwindow *win) : m_window(win) {
    //
}

std::shared_ptr<Canvas> Canvas::create(GLFWwindow *win) {
    return std::make_shared<Canvas>(win);
}

void Canvas::fill(const Vec4<uint8_t>& col) {
    glClearColor(col.x / 255.f, col.y / 255.f, col.z / 255.f, col.w / 255.f);
}

NS_SPECTRUM_END