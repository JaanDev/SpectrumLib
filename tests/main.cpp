#include <iostream>
#include "App.h"

void gameLoop(App* app){
    BeginDrawing();
        ClearBackground(WHITE);
        DrawText("Hello Jaan", 100, 100, 20, BLACK);
    EndDrawing();
}

int main() {
    App app;
    app.setGameLoopFunc(&gameLoop);

    return 0;
}