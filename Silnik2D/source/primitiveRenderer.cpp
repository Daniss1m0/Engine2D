﻿#include "PrimitiveRenderer.h"

PrimitiveRenderer::PrimitiveRenderer() : _display(nullptr) {
}

PrimitiveRenderer& PrimitiveRenderer::getInstance() {
    static PrimitiveRenderer instance;
    return instance;
}

void PrimitiveRenderer::Initialize(ALLEGRO_DISPLAY* display) {
    _display = display;
    if (!al_init_primitives_addon()) {
        std::cerr << "Błąd inicjalizacji dodatku do rysowania prymitywów." << std::endl;
    }
}

void PrimitiveRenderer::ClearScreen() {
    al_clear_to_color(al_map_rgb(0, 0, 0));
}

void PrimitiveRenderer::DrawPixel(float x, float y, const ALLEGRO_COLOR& color) {
    al_draw_pixel(x, y, color);
}

void PrimitiveRenderer::DrawLine(float x1, float y1, float x2, float y2, const ALLEGRO_COLOR& color, float thickness) {
    al_draw_line(x1, y1, x2, y2, color, thickness);
}

void PrimitiveRenderer::DrawTriangle(float x1, float y1, float x2, float y2, float x3, float y3, const ALLEGRO_COLOR& color) {
    al_draw_triangle(x1, y1, x2, y2, x3, y3, color, 1.0);
}

void PrimitiveRenderer::DrawFilledTriangle(float x1, float y1, float x2, float y2, float x3, float y3, const ALLEGRO_COLOR& color) {
    al_draw_filled_triangle(x1, y1, x2, y2, x3, y3, color);
}

void PrimitiveRenderer::DrawRectangle(float x, float y, float width, float height, const ALLEGRO_COLOR& color) {
    al_draw_rectangle(x, y, x + width, y + height, color, 1.0);
}

void PrimitiveRenderer::DrawFilledRectangle(float x, float y, float width, float height, const ALLEGRO_COLOR& color) {
    al_draw_filled_rectangle(x, y, x + width, y + height, color);
}

void PrimitiveRenderer::DrawRoundedRectangle(float x, float y, float width, float height, float rx, float ry, const ALLEGRO_COLOR& color) {
    al_draw_rounded_rectangle(x, y, x + width, y + height, rx, ry, color, 1.0);
}

void PrimitiveRenderer::DrawFilledRoundedRectangle(float x, float y, float width, float height, float rx, float ry, const ALLEGRO_COLOR& color) {
    al_draw_filled_rounded_rectangle(x, y, x + width, y + height, rx, ry, color);
}

void PrimitiveRenderer::DrawCircle(float x, float y, float radius, const ALLEGRO_COLOR& color) {
    al_draw_circle(x, y, radius, color, 1.0);
}

void PrimitiveRenderer::DrawFilledCircle(float x, float y, float radius, const ALLEGRO_COLOR& color) {
    al_draw_filled_circle(x, y, radius, color);
}

void PrimitiveRenderer::DrawEllipse(float cx, float cy, float rx, float ry, const ALLEGRO_COLOR& color) {
    al_draw_ellipse(cx, cy, rx, ry, color, 1.0);
}

void PrimitiveRenderer::DrawFilledEllipse(float cx, float cy, float rx, float ry, const ALLEGRO_COLOR& color) {
    al_draw_filled_ellipse(cx, cy, rx, ry, color);
}

void PrimitiveRenderer::DrawArc(float cx, float cy, float r, float start_theta, float end_theta, const ALLEGRO_COLOR& color) {
    al_draw_arc(cx, cy, r, start_theta, end_theta, color, 1.0);
}

void PrimitiveRenderer::FlipDisplay() {
    if (_display) {
        al_flip_display();
    }
}

void PrimitiveRenderer::DrawLineIncremental(float x1, float y1, float x2, float y2, const ALLEGRO_COLOR& color, float lineWidth) {
    float dx = fabs(x2 - x1);
    float dy = fabs(y2 - y1);
    float x = x1;
    float y = y1;
    float sx = (x1 < x2) ? 1.0f : -1.0f;
    float sy = (y1 < y2) ? 1.0f : -1.0f;

    if (dx > dy) {
        float error = dx / 2.0f;
        while (x != x2) {
            for (float i = -lineWidth / 2.0f; i < lineWidth / 2.0f; i += 1.0f) {
                al_draw_pixel(x, y + i, color);
            }
            error -= dy;
            if (error < 0) {
                y += sy;
                error += dx;
            }
            x += sx;
        }
    } 
    else {
        float error = dy / 2.0f;
        while (y != y2) {
            for (float i = -lineWidth / 2.0f; i < lineWidth / 2.0f; i += 1.0f) {
                al_draw_pixel(x + i, y, color);
            }
            error -= dx;
            if (error < 0) {
                x += sx;
                error += dy;
            }
            y += sy;
        }
    }
}


void PrimitiveRenderer::DrawPolyline(const std::vector<Point2D>& points, const ALLEGRO_COLOR& color, float lineWidth) {
    if (points.size() < 2) {
        std::cout << "linia lamana musi miec wiecej niz 1 punkt" << std::endl;
        return;
    }

    for (size_t i = 0; i < points.size() - 1; ++i) {
        DrawLine(points[i].GetX(), points[i].GetY(), points[i + 1].GetX(), points[i + 1].GetY(), color, lineWidth);
    }
}

void PrimitiveRenderer::DrawPolyline(const std::vector<LineSegment>& lineSegments, const ALLEGRO_COLOR& color, float lineWidth) {
    for (const LineSegment& segment : lineSegments) {
        DrawLine(segment.GetStartPoint().GetX(), segment.GetStartPoint().GetY(), segment.GetEndPoint().GetX(), segment.GetEndPoint().GetY(), color, lineWidth);
    }
}

std::vector<Point2D> PrimitiveRenderer::GenerateSquareSpiralPoints(float centerX, float centerY, int numTurns, float sideLength) {
    std::vector<Point2D> spiralPoints;

    float x = centerX;
    float y = centerY;
    spiralPoints.push_back(Point2D(x, y));
    x = x + sideLength;
    spiralPoints.push_back(Point2D(x,y));

    Vector2 lastVector(sideLength, 0.0);
    int i = 0;
    for (i = 0; i < numTurns; i++) {
       
        Vector2 rightVector = lastVector.Unit().RightVector()*(lastVector.Magnitude()+sideLength);

        float xS = x;
        float yS = y;

        x += rightVector.x;
        y += rightVector.y;

        lastVector.x = x - xS;
        lastVector.y = y - yS;

        Point2D newPoint(x, y);

        spiralPoints.push_back(newPoint);
        
    }

    return spiralPoints;
}