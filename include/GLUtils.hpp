#pragma once
#include "Includes.hpp"

NS_SPECTRUM_BEGIN

namespace gl {
    // inline void prepareGL() {
    //     if (!glfwInit()) {
    //         const char* error;
    //         int code = glfwGetError(&error);

    //         utils::logE("Failed to initialize glfw ({}; code {})", error, code);
    //         exit(1);
    //     }

    //     // utils::logD("OpenGL version: {}", (const char*)glGetString(GL_VERSION));
    //     // utils::logD("Renderer:       {}", (const char*)glGetString(GL_RENDERER));
    //     // utils::logD("Vendor:         {}", (const char*)glGetString(GL_VENDOR));
    //     // utils::logD("GLSL Version:   {}", (const char*)glGetString(GL_VERSION));

    //     preparedGL = true;
    // }
}

NS_SPECTRUM_END