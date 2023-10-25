#include "primitiveRenderer.h"

bool PrimitiveRenderer::Init()
{
    if (!al_init_primitives_addon()) {
        std::cerr << "B³¹d inicjalizacji dodatku do rysowania prymitywów." << std::endl;
        return false;
    }
    return true;
}

static PrimitiveRenderer&::getInstance() {
    static PrimitiveRenderer instance; // Statyczna instancja klasy
    return instance;
}

void PrimitiveRenderer::ClearScreen() {
    al_clear_to_color(al_map_rgb(0, 0, 0)); // Czyszczenie ekranu na czarno
}

void PrimitiveRenderer::DrawRectangle(float x, float y, float width, float height, ALLEGRO_COLOR color) {
    al_draw_filled_rectangle(x, y, x + width, y + height, color);
}

void PrimitiveRenderer::DrawCircle(float x, float y, float radius, ALLEGRO_COLOR color) {
    al_draw_filled_circle(x, y, radius, color);
}

void PrimitiveRenderer::FlipDisplay() {
    al_flip_display(); // Aktualizacja ekranu
}
