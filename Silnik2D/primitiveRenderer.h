#pragma once
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>

class PrimitiveRenderer {
public:
    static PrimitiveRenderer& getInstance();

    void Initialize(ALLEGRO_DISPLAY* display);

    void ClearScreen();
    void DrawRectangle(float x, float y, float width, float height, ALLEGRO_COLOR color);
    void DrawCircle(float x, float y, float radius, ALLEGRO_COLOR color);
    void DrawEllipse(float cx, float cy, float rx, float ry, ALLEGRO_COLOR color);
    void FlipDisplay();

private:
    PrimitiveRenderer();
    PrimitiveRenderer(const PrimitiveRenderer&) = delete;
    void operator=(const PrimitiveRenderer&) = delete;

    ALLEGRO_DISPLAY* display_;
};