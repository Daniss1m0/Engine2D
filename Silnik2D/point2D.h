#pragma once

#include "primitiveRenderer.h"

class Point2D {
public: 
    Point2D(float x = 0.0f, float y = 0.0f);

    // Metody odczytu wsp�rz�dnych punktu
    float GetX() const;
    float GetY() const;

    // Metody modyfikacji wsp�rz�dnych punktu
    void SetX(float x);
    void SetY(float y);
    void SetPosition(float x, float y);

    // Metoda rysowania punktu
    void Draw(PrimitiveRenderer& renderer, ALLEGRO_COLOR color, float pointSize = 1.0f);

private:
    float x_;
    float y_;
};