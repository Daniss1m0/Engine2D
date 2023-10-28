#pragma once

//#include "primitiveRenderer.h"

class Point2D {
private:
    float _x;
    float _y;

public: 
    Point2D(float x = 0.0f, float y = 0.0f);

    float GetX() const;
    float GetY() const;

    void SetX(float x);
    void SetY(float y);
    void SetPosition(float x, float y);

   // void Draw(PrimitiveRenderer& renderer, ALLEGRO_COLOR color, float pointSize = 1.0f);
};