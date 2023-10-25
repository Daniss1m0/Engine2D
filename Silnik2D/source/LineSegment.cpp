#include "LineSegment.h"

LineSegment::LineSegment(Point2D start, Point2D end) : start_(start), end_(end) {}

Point2D LineSegment::GetStartPoint() const {
    return start_;
}

Point2D LineSegment::GetEndPoint() const {
    return end_;
}

void LineSegment::SetStartPoint(Point2D start) {
    start_ = start;
}

void LineSegment::SetEndPoint(Point2D end) {
    end_ = end;
}

/*void LineSegment::Draw(PrimitiveRenderer& renderer, ALLEGRO_COLOR color, float grubosc, bool przyrostowy) {
    if (przyrostowy) {
        renderer.DrawLineIncremental(start_.GetX(), start_.GetY(), end_.GetX(), end_.GetY(), color, grubosc);
    }
    else {
        renderer.DrawLine(start_.GetX(), start_.GetY(), end_.GetX(), end_.GetY(), color, grubosc);
    }
}*/
