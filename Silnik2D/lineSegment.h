#pragma once

#include "point2D.h"

class LineSegment {
public:
    LineSegment(const Point2D& start, const Point2D& end);

    // Metoda zwracaj�ca pocz�tkowy punkt odcinka
    const Point2D& GetStart() const;

    // Metoda zwracaj�ca ko�cowy punkt odcinka
    const Point2D& GetEnd() const;

private:
    Point2D start_;
    Point2D end_;
};