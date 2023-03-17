#include "GLUtils.hpp"

NS_SPECTRUM_BEGIN

namespace glutils {
    void prepareRender(std::shared_ptr<Window> win) {
        auto winSize = win->getSize();
        glClear(GL_COLOR_BUFFER_BIT);
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        gluOrtho2D(0, winSize.x, winSize.y, 0);
        glViewport(0, 0, winSize.x, winSize.y);
    }
}

NS_SPECTRUM_END