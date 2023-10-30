#include "utils.hpp"

#include "logger.hpp"

NS_SPECTRUM_BEGIN

namespace utils {
    void glfwErrorCallback(int error, const char* description) {
        logE("GLFW Error: {} (code {})", description, error);
    }

    void initialize() {
        static bool initialized = false;

        if (initialized) {
            // logW("SpectrumLib has already been initialized");
            return;
        }

        if (!glfwInit()) {
            logE("Failed to initialize GLFW!");
            exit(1);
        }

        glfwSetErrorCallback(glfwErrorCallback);

        initialized = true;
    }

    void shutdown() {
        static bool hasShutdown = false;

        if (hasShutdown) {
            // logW("SpectrumLib has already been shut down");
            return;
        }

        glfwTerminate();

        hasShutdown = true;
    }
}

NS_SPECTRUM_END