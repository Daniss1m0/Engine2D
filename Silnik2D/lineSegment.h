#pragma once

#include "point2D.h"

class LineSegment {
public:
    LineSegment(const Point2D& start, const Point2D& end);

    // Metoda zwracająca początkowy punkt odcinka
    const Point2D& GetStart() const;

    // Metoda zwracająca końcowy punkt odcinka
    const Point2D& GetEnd() const;

private:
    Point2D start_;
    Point2D end_;
};