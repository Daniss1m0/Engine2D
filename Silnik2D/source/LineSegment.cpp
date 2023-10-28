#include "LineSegment.h"

LineSegment::LineSegment(Point2D start, Point2D end) : _start(start), _end(end) {}

const Point2D& LineSegment::GetStartPoint() const {
    return _start;
}

const Point2D& LineSegment::GetEndPoint() const {
    return _end;
}

void LineSegment::SetStartPoint(Point2D start) {
    _start = start;
}

void LineSegment::SetEndPoint(Point2D end) {
    _end = end;
}

#if 0
void LineSegment::Draw(PrimitiveRenderer& renderer, const ALLEGRO_COLOR& color, float grubosc, bool additive) {
    if (additive) {
        renderer.DrawLineIncremental(_start.GetX(), _start.GetY(), _end.GetX(), _end.GetY(), color, grubosc);
    }
    else {
        renderer.DrawLine(_end.GetX(), _end.GetY(), _end.GetX(), _end.GetY(), color, grubosc);
    }
}
#endif
