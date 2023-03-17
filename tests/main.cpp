#include "Spectrum.hpp"

using namespace spectrum;
using std::cout, std::endl;

int main() {
    auto win = Window::create("Hello Spectrum!", { 800, 600 }, {});

    std::cout << "Window created" << std::endl;

    utils::logE("Sample text");
    utils::logW("Sample text");
    utils::logD("Sample text");

    // win->setCloseCallback([](Window*) {
    //     std::cout << "Window closed" << std::endl;
    // });

    // win->setPosCallback([](Window*, Vec2 pos) {
    //     std::cout << "Window pos: " << pos << std::endl;
    // });

    // win->setSizeCallback([](Window*, Vec2 size) {
    //     std::cout << "Window size: " << size << std::endl;
    // });

    // win->setRefreshCallback([](Window*) {
    //     std::cout << "Refresh" << std::endl;
    // });

    // win->setWindowFocusCallback([](Window*, bool focused) {
    //     std::cout << "Window focused: " << std::boolalpha << focused << std::endl;
    // });

    // win->setContentScaleCallback([](Window*, Vec2 scale) {
    //     std::cout << "Window content scale: " << scale << std::endl;
    // });

    // win->setWindowIconifyCallback([](Window*, bool iconified) {
    //     std::cout << "Window iconified: " << std::boolalpha << iconified << std::endl;
    // });

    // win->setWindowMaximizeCallback([](Window*, bool maximized) {
    //     std::cout << "Window maximized: " << std::boolalpha << maximized << std::endl;
    // });

    // win->setFramebufferSizeCallback([](Window*, Vec2 size) {
    //     std::cout << "Framebuffer size: " << size << std::endl;
    // });

    // glfwSwapInterval(0); // vsync = off

    auto canvas = win->getCanvas();
    
    while (!win->shouldClose()) {
        glutils::prepareRender(win);

        // auto t = glfwGetTime();
        // auto val = (sin(t) / 1.f / 2.f) + 0.5f;
        // glClearColor(val, val, val, 1.f);

        canvas->line({100, 200}, {300, 400}, {255, 255, 255, 255});
       
        win->swapBuffers();
        glfwPollEvents();
    }

    return 0;
}