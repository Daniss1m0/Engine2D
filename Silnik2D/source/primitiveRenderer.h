#pragma once

#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro.h>
#include <iostream>
#include <vector>
#include <stack>
#include "vector2.h"

class PrimitiveRenderer;

class Point2D {
private:
    float _x;
    float _y;

public:
    Point2D(float x = 0.0f, float y = 0.0f);

    float GetX() const;
    float GetY() const;

    void SetX(float x);
    void SetY(float y);
    void SetPosition(float x, float y);

    Point2D operator+(const Vector2& other)
    {
        return Point2D(_x + other.x, _y + other.y);
    }

    Point2D operator*(float number)
    {
        return Point2D(_x * number, _y * number);
    }

    // void Draw(PrimitiveRenderer& renderer, ALLEGRO_COLOR color, float pointSize = 1.0f);
};

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
private:
    PrimitiveRenderer();
    PrimitiveRenderer(const PrimitiveRenderer&) = delete;
    void operator=(const PrimitiveRenderer&) = delete;

    ALLEGRO_DISPLAY* _display;

public:
    static PrimitiveRenderer& getInstance();

    void Initialize(ALLEGRO_DISPLAY* display);

    void ClearScreen();
    void DrawPixel(Point2D point, const ALLEGRO_COLOR& color);
    void DrawLine(Point2D start, Point2D end, const ALLEGRO_COLOR& color, float thickness);
    void DrawLineIncremental(Point2D start, Point2D end, const ALLEGRO_COLOR& color, float lineWidth);
    void DrawTriangle(Point2D point1, Point2D point2, Point2D point3, const ALLEGRO_COLOR& color);
    void DrawFilledTriangle(Point2D point1, Point2D point2, Point2D point3, const ALLEGRO_COLOR& color);
    void DrawRectangle(Point2D point, float width, float height, const ALLEGRO_COLOR& color);
    void DrawFilledRectangle(Point2D point, float width, float height, const ALLEGRO_COLOR& color);
    void DrawRoundedRectangle(Point2D point, float width, float height, float rx, float ry, const ALLEGRO_COLOR& color);
    void DrawFilledRoundedRectangle(Point2D point, float width, float height, float rx, float ry, const ALLEGRO_COLOR& color);
    void DrawCircle(Point2D point, float radius, const ALLEGRO_COLOR& color);
    void DrawCircleSymmetry4(Point2D p, float radius, ALLEGRO_COLOR color);
    void DrawFilledCircle(Point2D point, float radius, const ALLEGRO_COLOR& color);
    void DrawEllipse(Point2D point, float rx, float ry, const ALLEGRO_COLOR& color);
    void DrawEllipseSymmetry4(Point2D point, float rx, float ry, const ALLEGRO_COLOR& color);
    void DrawFilledEllipse(Point2D point, float rx, float ry, const ALLEGRO_COLOR& color);
    void DrawArc(Point2D point, float r, float start_theta, float end_theta, const ALLEGRO_COLOR& color);
    void DrawClosedPolygon(const std::vector<Point2D>& points, const ALLEGRO_COLOR& color, float thickness);

    void DrawPolyline(const std::vector<Point2D>& points, const ALLEGRO_COLOR& color, float lineWidth);
    void DrawPolyline(const std::vector<LineSegment>& lineSegments, const ALLEGRO_COLOR& color, float lineWidth);
    std::vector<Point2D> GenerateSquareSpiralPoints(float centerX, float centerY, int numTurns, float sideLength);
    //stosowac funkcji wypelniania obszaru kolorem tylko dla malych prymitywow
    void boundaryFill(int x, int y, const ALLEGRO_COLOR& fill_color, const ALLEGRO_COLOR& boundary_color);
    void floodFill(int x, int y, const ALLEGRO_COLOR& fill_color, const ALLEGRO_COLOR& background_color);
    bool colorsAreEqual(const ALLEGRO_COLOR& color1, const ALLEGRO_COLOR& color2);
    void checkAndAddPixel(std::stack<Point2D>& pixelsToCheck, const Point2D& point, const ALLEGRO_COLOR& fillColor, const ALLEGRO_COLOR& backgroundColor);

    void FlipDisplay();
};