#include <Spectrum.hpp>

using namespace spectrum;

int main() {
    auto win = Window::create("Hello Spectrum!", { 800, 600 }, {{ WindowHints::Decorated, true}});

    std::cout << "Window created" << std::endl;

    win->setCloseCallback([](Window*) {
        std::cout << "Window closed" << std::endl;
    });

    win->setPosCallback([](Window*, Vec2 pos) {
        std::cout << "Window pos: " << pos << std::endl;
    });

    win->setSizeCallback([](Window*, Vec2 size) {
        std::cout << "Window size: " << size << std::endl;
    });

    win->setRefreshCallback([](Window*) {
        std::cout << "Refresh" << std::endl;
    });

    win->setWindowFocusCallback([](Window*, bool focused) {
        std::cout << "Window focused: " << std::boolalpha << focused << std::endl;
    });

    win->setContentScaleCallback([](Window*, Vec2 scale) {
        std::cout << "Window content scale: " << scale << std::endl;
    });

    win->setWindowIconifyCallback([](Window*, bool iconified) {
        std::cout << "Window iconified: " << std::boolalpha << iconified << std::endl;
    });

    win->setWindowMaximizeCallback([](Window*, bool maximized) {
        std::cout << "Window maximized: " << std::boolalpha << maximized << std::endl;
    });

    win->setFramebufferSizeCallback([](Window*, Vec2 size) {
        std::cout << "Framebuffer size: " << size << std::endl;
    });
    
    while (!win->shouldClose()) {
        glClear(GL_COLOR_BUFFER_BIT);

        glClearColor(1, 0, 1, 1);

        win->swapBuffers();
        glfwPollEvents();
    }

    return 0;
}