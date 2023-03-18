#include "Canvas.hpp"

NS_SPECTRUM_BEGIN

Canvas::Canvas(GLFWwindow *win) : m_window(win) {
    //
}

std::shared_ptr<Canvas> Canvas::create(GLFWwindow *win) {
    return std::make_shared<Canvas>(win);
}

void Canvas::fill(const Col4& col) {
    glClearColor(col.x / 255.f, col.y / 255.f, col.z / 255.f, col.w / 255.f);
}

void Canvas::line(const Vec2i &start, const Vec2i &end, const Col4 &col, const float width) {
    if (width == 1.0f) { // if we have the default 1px width no need to do all those calculations
        glBegin(GL_LINES);
            glColor4ub(col.x, col.y, col.z, col.w);
            glVertex2i(start.x, start.y);
            glVertex2i(end.x, end.y);
        glEnd();
        return;
    }
    // glLineWidth(width);
    // auto angle = atan((start.x - end.x)/(start.y-end.y));
    auto x = abs(start.x - end.x);
    auto y = abs(start.y - end.y);
    // auto angle = atan2(y,x) * 180 / 3.14159;
    auto angle = atan2f(y,x);
    // utils::logD("{}, {}, {}", angle, x, y);

    // auto p1 = start + Vec2i {0, (width / 2.f)};
    // auto p1 = Vec2i {(sin(angle)*(width/2.f)+start.x), (cos(angle)*(width/2.f)+start.y)};
    // auto p2 = Vec2i {(-sin(angle)*(width/2.f)+start.x), (-cos(angle)*(width/2.f)+start.y)};
    // // auto p2 = start - Vec2i {0, (width / 2.f)};
    // auto p3 = end + Vec2i {0, (width / 2.f)};
    // auto p4 = end - Vec2i {0, (width / 2.f)};
    // glBegin(GL_QUADS);
    //     glColor4ub(col.x, col.y, col.z, col.w);
    //     // glVertex2i(start.x, start.y);
    //     // glVertex2i(end.x, end.y);
    //     glVertex2i(p1.x,p1.y);
    //     glVertex2i(p2.x,p2.y);
    //     glVertex2i(p3.x,p3.y);
    //     glVertex2i(p4.x,p4.y);
    // glEnd();

    auto offset = Vec2i { static_cast<int>(sinf(angle) * (width / 2.f)), static_cast<int>(-cosf(angle) * (width/2.f)) };

    auto p1 = start + offset;
    auto p2 = start - offset;

    auto p3 = end + offset;
    auto p4 = end - offset;

    // auto p1 = Vec2f { sinf(angle) * (width / 2.f) + start.x, -cosf(angle) * (width/2.f) + start.y };
    // auto p2 = Vec2f { -sinf(angle) * (width / 2.f) + start.x, cosf(angle) * (width/2.f) + start.y };
    
    // auto p3 = Vec2f { sinf(angle) * (width / 2.f) + end.x, -cosf(angle) * (width/2.f) + end.y };
    // auto p4 = Vec2f { -sinf(angle) * (width / 2.f) + end.x, cosf(angle) * (width/2.f) + end.y };
    // auto p1 = Vec2f { sinf(angle) * (width / 2.f) + start.x };
    glBegin(GL_QUADS);
        glColor4ub(col.x, col.y, col.z, col.w);
        glVertex2i(p1.x, p1.y);
        glVertex2i(p2.x, p2.y);
        glVertex2i(p4.x, p4.y);
        glVertex2i(p3.x, p3.y);
        // glVertex2i(start.x, start.y);
    glEnd();
}

NS_SPECTRUM_END