#ifndef __SPECTRUM__APP_H__
#define __SPECTRUM__APP_H__

#include "includes.h"
#include "Scene.h"

class App {
private:
    void AppInit();
    void updateFrame();
    void CloseApp();

    unsigned int m_nFps = 60;
    Vector2 m_vResolution = {640, 480};
    std::string title = "Game";
    Scene* currentscene;

public:
    App();
    App* getInstance();
    void setWindowName(std::string name);
};

#endif