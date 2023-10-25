#include "Point2D.h"

Point2D::Point2D(float x, float y) : x_(x), y_(y) {
}

float Point2D::GetX() const {
    return x_;
}

float Point2D::GetY() const {
    return y_;
}

void Point2D::SetX(float x) {
    x_ = x;
}

void Point2D::SetY(float y) {
    y_ = y;
}

void Point2D::SetPosition(float x, float y) {
    x_ = x;
    y_ = y;
}

void Point2D::Draw(PrimitiveRenderer& renderer, ALLEGRO_COLOR color, float pointSize) {
    renderer.DrawFilledCircle(x_, y_, pointSize, color);
}