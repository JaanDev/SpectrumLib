#pragma once
#include "Includes.hpp"
// #include "Window.hpp"

NS_SPECTRUM_BEGIN

class Window;

namespace glutils {
    void prepareRender(std::shared_ptr<Window> win);
}

NS_SPECTRUM_END