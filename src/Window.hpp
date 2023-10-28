#pragma once
#include <string>
#include "utils.hpp"
#include "types.hpp"

NS_SPECTRUM_BEGIN

class Window {
  public:
    Window(const std::string& title, const Sizei& size);
    ~Window();

    inline bool shouldClose() const { return glfwWindowShouldClose(m_window); }
    inline GLFWwindow* getWindow() const { return m_window; }

  private:
    GLFWwindow* m_window;
};

NS_SPECTRUM_END