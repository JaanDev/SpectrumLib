#include <Spectrum.hpp>

#include <functional>

template <typename T>
class ActionLerp {
  public:
    ActionLerp(int easing, float duration, T startVal, T endVal, std::function<void(T)> callback);

  private:
    T m_startVal;
    T m_endVal;
};

int main() {
    spl::Window win("Hello Spectrum!", {800, 600});

    while (!win.shouldClose()) {
        glfwPollEvents();

        auto val = sin(glfwGetTime() * 1.5) / 2.0 + 0.5;

        glClearColor(val, .5, .5, 1);
        glClear(GL_COLOR_BUFFER_BIT);

        glfwSwapBuffers(win.getWindow());
    }

    return 0;
}