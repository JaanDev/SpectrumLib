#include "App.h"

App::App(){
    this->AppInit();
}

void App::AppInit(){
    InitWindow(this->m_vResolution.x, this->m_vResolution.y, this->title.c_str());
    SetTargetFPS(this->m_nFps);
    while(!WindowShouldClose()){
        this->updateFrame();
    }

    this->CloseApp();
}

void App::updateFrame(){
    ClearBackground(this->currentscene->getColor());
    BeginDrawing();

    EndDrawing();
}

void App::CloseApp(){
    CloseWindow();
}