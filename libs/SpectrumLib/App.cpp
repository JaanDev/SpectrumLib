#include "App.h"

App::App(){
    InitWindow(width, height, title.c_str());
    this->setInitFunc([&](App* app){
        SetTargetFPS(this->fps);
        SetConfigFlags(this->flags);
    });

    this->setCloseFunc([&](App* app){
        CloseWindow();
    });
}

void App::setTitle(string title){
    SetWindowTitle(title.c_str());
}

void App::setResolution(Vector2 resolution){
    SetWindowSize(resolution.x, resolution.y);
}

void App::setInitFunc(std::function<void(App* app)> init){
    this->init = init;
    init(this);
}

void App::setGameLoopFunc(std::function<void(App* app)> update){
    this->update = update;
    while(!WindowShouldClose()){
        update(this);
    }

    this->close(this);
}

void App::setCloseFunc(std::function<void(App* app)> close){
    this->close = close;
}