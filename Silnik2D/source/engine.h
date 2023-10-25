#pragma once


#include <iostream>
#include "primitiveRenderer.h"

class Engine {
private:
    ALLEGRO_DISPLAY* display = nullptr;
    ALLEGRO_EVENT_QUEUE* eventQueue = nullptr;
    ALLEGRO_TIMER* fpsTimer = nullptr;
    const int screenWidth = 0;
    const int screenHeight = 0;
    const float FPS = 60.0f;

public:
    Engine(int width, int height, float fps = 60.0f);
    bool Init();
    void Run();
    void Deinit();
};

