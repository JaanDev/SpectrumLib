#include "App.h"

App::App(){
    this->AppInit();
}

void App::AppInit(){
    InitWindow((int)this->m_vResolution.x, (int)this->m_vResolution.y, this->title.c_str());
    SetTargetFPS(this->m_nFps);

    Scene* defaultscene = new(std::nothrow) Scene();
    this->currentscene = defaultscene;

    while(!WindowShouldClose()){
        this->updateFrame();
    }

    this->CloseApp();
}

void App::updateFrame(){
    BeginDrawing();
        ClearBackground(this->currentscene->getColor());

    EndDrawing();
}

void App::CloseApp(){
    CloseWindow();
}

void App::setWindowName(std::string name){
    this->title = name;
    SetWindowTitle(title.c_str());
}