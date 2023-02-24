#pragma once
#include "Includes.hpp"

enum class WindowAttribs {
    Decorated = GLFW_DECORATED,
    Resizable = GLFW_RESIZABLE,
    Floating = GLFW_FLOATING,
    AutoIconify = GLFW_AUTO_ICONIFY,
    FocusOnShow = GLFW_FOCUS_ON_SHOW
};

enum class WindowHints {
    Resizable = GLFW_RESIZABLE,
    Visible = GLFW_VISIBLE,
    Decorated = GLFW_DECORATED,
    Focused = GLFW_FOCUSED,
    AutoIconify = GLFW_AUTO_ICONIFY,
    Floating = GLFW_FLOATING,
    Maximized = GLFW_MAXIMIZED,
    CenterCursor = GLFW_CENTER_CURSOR,
    TransparentFramebuffer = GLFW_TRANSPARENT_FRAMEBUFFER,
    FocusOnShow = GLFW_FOCUS_ON_SHOW,
    ScaleToMonitor = GLFW_SCALE_TO_MONITOR
};