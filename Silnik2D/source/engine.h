#pragma once

#include <iostream>
#include <game.h>

class Engine {
private:
    ALLEGRO_DISPLAY* _display = nullptr;
    ALLEGRO_EVENT_QUEUE* _eventQueue = nullptr;
    ALLEGRO_TIMER* _fpsTimer = nullptr;
    const int _screenWidth = 0;
    const int _screenHeight = 0;
    const float _FPS = 60.0f;

public:
    Engine(int width, int height, float fps = 60.0f);
    bool Init();
    void Run();
    void Deinit();
};