#include "LineSegment.h"

LineSegment::LineSegment(Point2D start, Point2D end) : _start(start), _end(end) {}

Point2D LineSegment::GetStartPoint() const {
    return _start;
}

Point2D LineSegment::GetEndPoint() const {
    return _end;
}

void LineSegment::SetStartPoint(Point2D start) {
    _start = start;
}

void LineSegment::SetEndPoint(Point2D end) {
    _end = end;
}

/*void LineSegment::Draw(PrimitiveRenderer& renderer, ALLEGRO_COLOR color, float grubosc, bool przyrostowy) {
    if (przyrostowy) {
        renderer.DrawLineIncremental(start_.GetX(), start_.GetY(), end_.GetX(), end_.GetY(), color, grubosc);
    }
    else {
        renderer.DrawLine(start_.GetX(), start_.GetY(), end_.GetX(), end_.GetY(), color, grubosc);
    }
}*/
