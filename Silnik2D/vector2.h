#pragma once

#include <math.h>

class Vector2 {
public:
    float x;
    float y;
    Vector2(float x = 0.0f, float y = 0.0f);
    
    Vector2 Unit();
    Vector2 RightVector();
    float Magnitude();

    Vector2 operator*(const Vector2& other) {
        return Vector2(x * other.x, y * other.y);
    }

    Vector2 operator*(float other) {
        return Vector2(x * other, y * other);
    }

};