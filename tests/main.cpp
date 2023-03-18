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

    glfwSwapInterval(0); // vsync = off

    auto canvas = win->getCanvas();
    auto lastT = glfwGetTime();
    while (!win->shouldClose()) {
        glutils::prepareRender(win);
        auto t = glfwGetTime();
        utils::logD("FPS: {:.2f}", 1.0/(t - lastT));
        lastT = t;
        
        // drawing code

        auto val = (sin(t) / 2.f) + 0.5f; // 0 to 1
        canvas->fill({ (uint8_t)(val*255), (uint8_t)(val*255), (uint8_t)(val*255), 1 });

        canvas->line({ 100, 200 }, { 500, 200 + (int)(val*200) }, { 255, 0, 0, 255 }, val*15.f + 5.f);
        // canvas->line({100, 200}, {500, 200 + (int)(val*200)}, {255, 0, 0, 255}, 2);
       
        win->swapBuffers();
        glfwPollEvents();
    }

    return 0;
}