#include <iostream>
#include <string>
#include <functional>
#include "raylib.h"

using std::string;

class App {
    private:
        std::string title = "Spectrum App";
        uint16_t width = 900;
        uint16_t height = 600;
        std::function<void(App* app)> init;
        std::function<void(App* app)> update;
        std::function<void(App* app)> close;
        uint32_t fps = 60;
        uint32_t flags = FLAG_WINDOW_RESIZABLE;

    public:
        App* create(string title, uint16_t width, uint16_t height);
        void setTitle(string title);
        void setResolution(Vector2 resolution);
        void setInitFunc(std::function<void(App* app)> init);
        void setGameLoopFunc(std::function<void(App* app)> update);
        void setCloseFunc(std::function<void(App* app)> close);
    App();
};