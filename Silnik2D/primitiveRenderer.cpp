#include "PrimitiveRenderer.h"
#include <iostream>

PrimitiveRenderer::PrimitiveRenderer() : display_(nullptr) {
}

PrimitiveRenderer& PrimitiveRenderer::getInstance() {
    static PrimitiveRenderer instance;
    return instance;
}

void PrimitiveRenderer::Initialize(ALLEGRO_DISPLAY* display) {
    display_ = display;
    if (!al_init_primitives_addon()) {
        std::cerr << "B³¹d inicjalizacji dodatku do rysowania prymitywów." << std::endl;
    }
}

void PrimitiveRenderer::ClearScreen() {
    al_clear_to_color(al_map_rgb(0, 0, 0));
}

void PrimitiveRenderer::DrawRectangle(float x, float y, float width, float height, ALLEGRO_COLOR color) {
    al_draw_filled_rectangle(x, y, x + width, y + height, color);
}

void PrimitiveRenderer::DrawCircle(float x, float y, float radius, ALLEGRO_COLOR color) {
    al_draw_filled_circle(x, y, radius, color);
}

void PrimitiveRenderer::DrawEllipse(float cx, float cy, float rx, float ry, ALLEGRO_COLOR color) {
    al_draw_filled_ellipse(cx, cy, rx, ry, color);
}

void PrimitiveRenderer::FlipDisplay() {
    if (display_) {
        al_flip_display();
    }
}