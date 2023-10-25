#pragma once

#include "point2D.h"

class LineSegment {
public:
    LineSegment(const Point2D& start, const Point2D& end);

    // Metoda zwracaj¹ca pocz¹tkowy punkt odcinka
    const Point2D& GetStart() const;

    // Metoda zwracaj¹ca koñcowy punkt odcinka
    const Point2D& GetEnd() const;

private:
    Point2D start_;
    Point2D end_;
};