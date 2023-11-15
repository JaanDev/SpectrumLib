#include "AppManager.hpp"

#include <thread>
#include <chrono>
#include <stack>
#include <glm/mat4x4.hpp>
#include <glm/gtx/transform.hpp>
#ifdef _WIN32
#include <Windows.h>
#endif
#include "logger.hpp"
#include "ActionManager.hpp"
#include "ShaderManager.hpp"
#include "Scheduler.hpp"

NS_SPECTRUM_BEGIN

AppManager* AppManager::instance() {
    static auto instance = std::make_unique<AppManager>();
    return instance.get();
}

AppManager::AppManager()
    : m_winSize({0, 0}), m_deltaTime(0.f), m_pointsToPixels({0.f, 0.f}), m_contentScale(1.f), m_scenes({}), m_currentScene(0),
      m_isRunning(false), m_isCursorVisible(true), m_isCursorLocked(false), m_timeScale(1.f), m_targetFrameTime(1.f / 60.f),
      m_curScene(nullptr) {}

void AppManager::run() {
    static bool hasRun = false;
    if (hasRun) {
        logW("AppManager::run has already been called");
        return;
    }
    hasRun = true;

    ShaderManager::instance();

    m_isRunning = true;

    auto win = WindowManager::instance()->getGLFWWindow();

    auto startTime = std::chrono::high_resolution_clock::now();

    auto getTime = [startTime]() {
        return std::chrono::duration<double>(std::chrono::high_resolution_clock::now() - startTime).count();
    };

    double lastFrameTime = 0.;
    int fps = 0;
    float fpsTime = 0.f;

    std::stack<glm::mat4> matrixStack;
    auto projMtx = glm::ortho(0.f, m_winSize.w, m_winSize.h, 0.f, -100.f, 100.f);
    matrixStack.push(projMtx);

    while (!glfwWindowShouldClose(win)) {
        auto frameStartTime = getTime();
        m_deltaTime = static_cast<float>((frameStartTime - lastFrameTime) * m_timeScale);

        fpsTime += static_cast<float>(frameStartTime - lastFrameTime);
        if (fpsTime >= 1.0f) {
            logD("{} FPS", fps);
            m_fps = fps;
            fps = 0;
            fpsTime = 0.f;
        }

        glfwPollEvents();

        if (!m_isRunning) {
            glfwSwapBuffers(win);
            lastFrameTime = getTime();
            continue;
        }

        // 1. process all the stuff

        ActionManager::instance()->update(m_deltaTime);
        Scheduler::instance()->update(m_deltaTime);

        Col3f currentColor = {0.f, 0.f, 0.f};
        if (m_curScene) {
            currentColor = m_curScene->getBGColor();

            std::function<void(Node*)> updateNodes;
            updateNodes = [this, &updateNodes](Node* node) {
                node->update(this->m_deltaTime);
                for (auto child : node->getChildren()) {
                    updateNodes(child.get());
                }
            };

            updateNodes(m_curScene);
        }

        // 2. draw all the stuff

        glClearColor(currentColor.r, currentColor.g, currentColor.b, 1.f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        if (m_curScene) {
            std::function<void(Node*)> drawNodes;
            drawNodes = [this, &drawNodes, &matrixStack](Node* node) {
                if (!node->isVisible())
                    return;

                matrixStack.push(matrixStack.top() * node->getMatrix());

                // TODO: remove gl matrix stuff
                glPushMatrix();
                glLoadMatrixf(&matrixStack.top()[0][0]);

                auto& children = node->getChildren();
                bool selfDrawn = false;
                for (auto child : children) {
                    if (child->getZOrder() == 0 && !selfDrawn) {
                        selfDrawn = true;
                        node->draw();
                    }

                    drawNodes(child.get());
                }

                if (!selfDrawn) {
                    node->draw();
                }

                // TODO: remove gl matrix stuff
                glPopMatrix();

                matrixStack.pop();
            };

            drawNodes(m_curScene);
        }

        glfwSwapBuffers(win);

        // 3. wait to maintain target FPS if needed

        // auto timeToWait = frameStartTime + m_targetFrameTime - getTime();
        // if (timeToWait > 0.f) {
        //     std::this_thread::sleep_for(std::chrono::duration<double>(timeToWait));
        // }

        lastFrameTime = frameStartTime;

        fps++;
    }

    matrixStack.pop();
}

void AppManager::pause() {
    m_isRunning = false;
}

void AppManager::resume() {
    m_isRunning = true;
}

void AppManager::end() {
    m_isRunning = false;
    glfwSetWindowShouldClose(WindowManager::instance()->getGLFWWindow(), true);
}

double AppManager::getTime() {
    return glfwGetTime();
}

void AppManager::setContentScale(float scale) {}

void AppManager::setCursorVisible(bool visible) {
    m_isCursorVisible = visible;
    glfwSetInputMode(WindowManager::instance()->getGLFWWindow(), GLFW_CURSOR, visible ? GLFW_CURSOR_NORMAL : GLFW_CURSOR_HIDDEN);
}

void AppManager::setCursorLocked(bool locked) {
    m_isCursorLocked = locked;
    glfwSetInputMode(WindowManager::instance()->getGLFWWindow(), GLFW_CURSOR, locked ? GLFW_CURSOR_DISABLED : GLFW_CURSOR_NORMAL);
}

void AppManager::openURL(const std::string& url) {
#ifdef _WIN32
    ShellExecute(0, 0, url.c_str(), 0, 0, SW_SHOW);
#elif defined(__linux__)
    system(fmt::format("xdg-open {}", url).c_str());
#else
    logW("AppManager::openURL is not implemented on your platform!");
#endif
}

void AppManager::setTimeScale(float ts) {
    this->m_timeScale = ts;
}

std::shared_ptr<Scene> AppManager::getCurrentScene() {
    return std::shared_ptr<Scene>();
}

void AppManager::pushScene(std::shared_ptr<Scene> scene) {
    m_scenes.push_back(scene);
    m_currentScene = m_scenes.size() - 1;
    m_curScene = scene.get();
}

void AppManager::replaceScene(std::shared_ptr<Scene> scene) {
    m_scenes[m_scenes.size() - 1] = scene;
    m_currentScene = m_scenes.size() - 1;
    m_curScene = scene.get();
}

void AppManager::goToScene(int step) {
    logW("AppMgr::goToScene todo");
}

std::string AppManager::getClipboardText() {
    auto str = glfwGetClipboardString(WindowManager::instance()->getGLFWWindow());
    return str ? str : "";
}

void AppManager::setClipboardText(const std::string& text) {
    glfwSetClipboardString(WindowManager::instance()->getGLFWWindow(), text.c_str());
}

Vec2f AppManager::pointsToPixels(const Vec2f& pointPos) {
    return pointPos / m_pointsToPixels;
}

Vec2f AppManager::pixelsToPoints(const Vec2f& pixelPos) {
    return pixelPos * m_pointsToPixels;
}

Sizef AppManager::pixelsToSize(const Sizef& pixelSize) {
    return pixelSize * m_pointsToPixels;
}

Sizef AppManager::sizeToPixels(const Sizef& size) {
    return size / m_pointsToPixels;
}

NS_SPECTRUM_END
