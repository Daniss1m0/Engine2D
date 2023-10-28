#include "vector2.h"

Vector2::Vector2(float x, float y) : x(x), y(y) {}

float Vector2::Magnitude()
{
	return sqrt(x * x + y * y);
}

Vector2 Vector2::Unit()
{
	if (Magnitude() == 0.0)
	{
		Vector2 newValue(0.0, 0.0);
		return newValue;
	}

	Vector2 newValue;
	newValue.x = x / Magnitude();
	newValue.y = y / Magnitude();
	return newValue;
}

Vector2 Vector2::RightVector()
{
	return Vector2(y, -x);
}
