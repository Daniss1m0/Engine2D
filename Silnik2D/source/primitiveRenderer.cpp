#include "primitiveRenderer.h"

PrimitiveRenderer& PrimitiveRenderer::GetInstance(ALLEGRO_DISPLAY* display) {
    static PrimitiveRenderer instance(display); // Statyczna instancja klasy
    return instance;
}

PrimitiveRenderer::PrimitiveRenderer(ALLEGRO_DISPLAY* display) : display_(display)
{
}

bool PrimitiveRenderer::Init()
{
    if (!al_init_primitives_addon()) {
        std::cerr << "B³¹d inicjalizacji dodatku do rysowania prymitywów." << std::endl;
        return false;
    }
    return true;
}


void PrimitiveRenderer::ClearScreen() {
    al_clear_to_color(al_map_rgb(0, 0, 0)); // Czyszczenie ekranu na czarno
}

void PrimitiveRenderer::DrawRectangle(float x, float y, float width, float height, const ALLEGRO_COLOR& color) {
    al_draw_filled_rectangle(x, y, x + width, y + height, color);
}

void PrimitiveRenderer::DrawCircle(float x, float y, float radius, const ALLEGRO_COLOR& color) {
    al_draw_filled_circle(x, y, radius, color);
}

void PrimitiveRenderer::FlipDisplay() {
    al_flip_display(); // Aktualizacja ekranu
}
