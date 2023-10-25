#pragma once
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <iostream>

class PrimitiveRenderer {
protected:
    ALLEGRO_DISPLAY* display_;
    PrimitiveRenderer() : display_(nullptr) {}
    PrimitiveRenderer(ALLEGRO_DISPLAY* display);
    PrimitiveRenderer(const PrimitiveRenderer&) = delete;
    void operator=(const PrimitiveRenderer&) = delete;
public:
    bool Init();
    static PrimitiveRenderer& GetInstance(ALLEGRO_DISPLAY* display);
    void ClearScreen();
    void DrawRectangle(float x, float y, float width, float height, const ALLEGRO_COLOR& color);
    void DrawCircle(float x, float y, float radius, const ALLEGRO_COLOR& color);
    void FlipDisplay();
};