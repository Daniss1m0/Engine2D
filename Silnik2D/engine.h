#pragma once

#ifndef ENGINE_H
#define ENGINE_H

#include <iostream>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>

class Engine {
private:
    ALLEGRO_DISPLAY* display;
    ALLEGRO_EVENT_QUEUE* eventQueue;
    ALLEGRO_TIMER* timer;
    const int screenWidth;
    const int screenHeight;
    const float FPS = 60.0f;

public:
    Engine(int width, int height);
    bool Init();
    void Run();
    void Deinit();
};

#endif