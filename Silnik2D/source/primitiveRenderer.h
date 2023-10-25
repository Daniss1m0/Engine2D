#pragma once

#include <iostream>
#include <vector>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include "LineSegment.h"
#include "vector2.h"

class PrimitiveRenderer {
public:
    static PrimitiveRenderer& getInstance();

    void Initialize(ALLEGRO_DISPLAY* display);

    void ClearScreen();
    void DrawPixel(float x, float y, ALLEGRO_COLOR color);
    void DrawLine(float x1, float y1, float x2, float y2, ALLEGRO_COLOR color, float thickness);
    void DrawTriangle(float x1, float y1, float x2, float y2, float x3, float y3, ALLEGRO_COLOR color);
    void DrawFilledTriangle(float x1, float y1, float x2, float y2, float x3, float y3, ALLEGRO_COLOR color);
    void DrawRectangle(float x, float y, float width, float height, ALLEGRO_COLOR color);
    void DrawFilledRectangle(float x, float y, float width, float height, ALLEGRO_COLOR color);
    void DrawRoundedRectangle(float x, float y, float width, float height, float rx, float ry, ALLEGRO_COLOR color);
    void DrawFilledRoundedRectangle(float x, float y, float width, float height, float rx, float ry, ALLEGRO_COLOR color);
    void DrawCircle(float x, float y, float radius, ALLEGRO_COLOR color);
    void DrawFilledCircle(float x, float y, float radius, ALLEGRO_COLOR color);
    void DrawEllipse(float cx, float cy, float rx, float ry, ALLEGRO_COLOR color);
    void DrawFilledEllipse(float cx, float cy, float rx, float ry, ALLEGRO_COLOR color);
    void DrawArc(float cx, float cy, float r, float start_theta, float end_theta, ALLEGRO_COLOR color);
    void DrawLineIncremental(float x1, float y1, float x2, float y2, ALLEGRO_COLOR color, float lineWidth);
    void DrawPolyline(const std::vector<Point2D>& points, ALLEGRO_COLOR color, float lineWidth);
    void DrawPolyline(const std::vector<LineSegment>& lineSegments, ALLEGRO_COLOR color, float lineWidth);
    std::vector<Point2D> GenerateSquareSpiralPoints(float centerX, float centerY, int numTurns, float sideLength);
    void FlipDisplay();

private:
    PrimitiveRenderer();
    PrimitiveRenderer(const PrimitiveRenderer&) = delete;
    void operator=(const PrimitiveRenderer&) = delete;

    ALLEGRO_DISPLAY* display_;
};