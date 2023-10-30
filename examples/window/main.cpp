#include <Spectrum.hpp>
#include <logger.hpp>

int main() {    
    spl::Window win("Hello Spectrum!", {800, 600});

    while (!win.shouldClose()) {
        glfwPollEvents();

        auto val = sin(glfwGetTime() * 1.5) / 2.0 + 0.5;

        // spl::logD("{}", val);

        glClearColor(val, .5, .5, 1);
        glClear(GL_COLOR_BUFFER_BIT);

        glfwSwapBuffers(win.getWindow());
    }
    
    return 0;
}