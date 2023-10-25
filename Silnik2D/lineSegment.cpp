#include "LineSegment.h"

LineSegment::LineSegment(const Point2D& start, const Point2D& end) : start_(start), end_(end) {
}

const Point2D& LineSegment::GetStart() const {
    return start_;
}

const Point2D& LineSegment::GetEnd() const {
    return end_;
}