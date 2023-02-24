#include <Window.hpp>

NS_SPECTRUM_BEGIN

std::shared_ptr<Window> Window::create(std::string_view title, Vec2 size) {
    return std::make_shared<Window>(title, size);
}

void Window::setTitle(const std::string& str) {
    glfwSetWindowTitle(m_window, str.c_str());
}

NS_SPECTRUM_END