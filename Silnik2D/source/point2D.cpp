#include "Point2D.h"

Point2D::Point2D(float x, float y) : _x(x), _y(y) {
}

float Point2D::GetX() const {
    return _x;
}

float Point2D::GetY() const {
    return _y;
}

void Point2D::SetX(float x) {
    _x = x;
}

void Point2D::SetY(float y) {
    _y = y;
}

void Point2D::SetPosition(float x, float y) {
    _x = x;
    _y = y;
}

/*void Point2D::Draw(PrimitiveRenderer& renderer, ALLEGRO_COLOR color, float pointSize) {
    renderer.DrawFilledCircle(x_, y_, pointSize, color);
}*/