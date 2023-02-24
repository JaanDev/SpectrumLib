#include <Spectrum.hpp>

using namespace spectrum;

int main() {
    auto win = Window::create("Hello Spectrum!", { 800, 600 });

    std::cout << "Window created" << std::endl;

    return 0;
}