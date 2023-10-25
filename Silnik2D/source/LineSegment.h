#pragma once

#include "Point2D.h"
//#include "PrimitiveRenderer.h"

class LineSegment {
private:
    Point2D start_;
    Point2D end_;

public:
    LineSegment(Point2D start, Point2D end);

    Point2D GetStartPoint() const;
    Point2D GetEndPoint() const;

    void SetStartPoint(Point2D start);
    void SetEndPoint(Point2D end);

    //void Draw(PrimitiveRenderer& renderer, ALLEGRO_COLOR color, float thickness, bool przyrostowy);
};

