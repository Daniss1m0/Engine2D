#pragma once

#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro.h>
#include <iostream>
#include <vector>
#include "vector2.h"
#include "point2D.h"

class PrimitiveRenderer;

class LineSegment {
private:
	Point2D _start;
	Point2D _end;

public:
	LineSegment(Point2D start, Point2D end);

	const Point2D& GetStartPoint() const;
	const Point2D& GetEndPoint() const;

	void SetStartPoint(Point2D start);
	void SetEndPoint(Point2D end);

	void Draw(PrimitiveRenderer& renderer, const ALLEGRO_COLOR& color, float thickness, bool additive);
};

class PrimitiveRenderer {
public:
    static PrimitiveRenderer& getInstance();

    void Initialize(ALLEGRO_DISPLAY* display);

    void ClearScreen();
    void DrawPixel(float x, float y, const const ALLEGRO_COLOR& color);
    void DrawLine(float x1, float y1, float x2, float y2, const ALLEGRO_COLOR& color, float thickness);
    void DrawTriangle(float x1, float y1, float x2, float y2, float x3, float y3, const ALLEGRO_COLOR& color);
    void DrawFilledTriangle(float x1, float y1, float x2, float y2, float x3, float y3, const ALLEGRO_COLOR& color);
    void DrawRectangle(float x, float y, float width, float height, const ALLEGRO_COLOR& color);
    void DrawFilledRectangle(float x, float y, float width, float height, const ALLEGRO_COLOR& color);
    void DrawRoundedRectangle(float x, float y, float width, float height, float rx, float ry, const ALLEGRO_COLOR& color);
    void DrawFilledRoundedRectangle(float x, float y, float width, float height, float rx, float ry, const ALLEGRO_COLOR& color);
    void DrawCircle(float x, float y, float radius, const ALLEGRO_COLOR& color);
    void DrawFilledCircle(float x, float y, float radius, const ALLEGRO_COLOR& color);
    void DrawEllipse(float cx, float cy, float rx, float ry, const ALLEGRO_COLOR& color);
    void DrawFilledEllipse(float cx, float cy, float rx, float ry, const ALLEGRO_COLOR& color);
    void DrawArc(float cx, float cy, float r, float start_theta, float end_theta, const ALLEGRO_COLOR& color);
    void DrawLineIncremental(float x1, float y1, float x2, float y2, const ALLEGRO_COLOR& color, float lineWidth);
    void DrawPolyline(const std::vector<Point2D>& points, const ALLEGRO_COLOR& color, float lineWidth);
    void DrawPolyline(const std::vector<LineSegment>& lineSegments, const ALLEGRO_COLOR& color, float lineWidth);
    std::vector<Point2D> GenerateSquareSpiralPoints(float centerX, float centerY, int numTurns, float sideLength);
    void FlipDisplay();

private:
    PrimitiveRenderer();
    PrimitiveRenderer(const PrimitiveRenderer&) = delete;
    void operator=(const PrimitiveRenderer&) = delete;

    ALLEGRO_DISPLAY* _display;
};