#include "PrimitiveRenderer.h"
#include <iostream>

PrimitiveRenderer::PrimitiveRenderer() : display_(nullptr) {
}

PrimitiveRenderer& PrimitiveRenderer::getInstance() {
    static PrimitiveRenderer instance;
    return instance;
}

void PrimitiveRenderer::Initialize(ALLEGRO_DISPLAY* display) {
    display_ = display;
    if (!al_init_primitives_addon()) {
        std::cerr << "Błąd inicjalizacji dodatku do rysowania prymitywów." << std::endl;
    }
}

void PrimitiveRenderer::ClearScreen() {
    al_clear_to_color(al_map_rgb(0, 0, 0));
}

void PrimitiveRenderer::DrawPixel(float x, float y, ALLEGRO_COLOR color) {
    al_draw_pixel(x, y, color);
}

void PrimitiveRenderer::DrawLine(float x1, float y1, float x2, float y2, ALLEGRO_COLOR color, float thickness) {
    al_draw_line(x1, y1, x2, y2, color, thickness);
}

void PrimitiveRenderer::DrawTriangle(float x1, float y1, float x2, float y2, float x3, float y3, ALLEGRO_COLOR color) {
    al_draw_triangle(x1, y1, x2, y2, x3, y3, color, 1.0);
}

void PrimitiveRenderer::DrawFilledTriangle(float x1, float y1, float x2, float y2, float x3, float y3, ALLEGRO_COLOR color) {
    al_draw_filled_triangle(x1, y1, x2, y2, x3, y3, color);
}

void PrimitiveRenderer::DrawRectangle(float x, float y, float width, float height, ALLEGRO_COLOR color) {
    al_draw_rectangle(x, y, x + width, y + height, color, 1.0);
}

void PrimitiveRenderer::DrawFilledRectangle(float x, float y, float width, float height, ALLEGRO_COLOR color) {
    al_draw_filled_rectangle(x, y, x + width, y + height, color);
}

void PrimitiveRenderer::DrawRoundedRectangle(float x, float y, float width, float height, float rx, float ry, ALLEGRO_COLOR color) {
    al_draw_rounded_rectangle(x, y, x + width, y + height, rx, ry, color, 1.0);
}

void PrimitiveRenderer::DrawFilledRoundedRectangle(float x, float y, float width, float height, float rx, float ry, ALLEGRO_COLOR color) {
    al_draw_filled_rounded_rectangle(x, y, x + width, y + height, rx, ry, color);
}

void PrimitiveRenderer::DrawCircle(float x, float y, float radius, ALLEGRO_COLOR color) {
    al_draw_circle(x, y, radius, color, 1.0);
}

void PrimitiveRenderer::DrawFilledCircle(float x, float y, float radius, ALLEGRO_COLOR color) {
    al_draw_filled_circle(x, y, radius, color);
}

void PrimitiveRenderer::DrawEllipse(float cx, float cy, float rx, float ry, ALLEGRO_COLOR color) {
    al_draw_ellipse(cx, cy, rx, ry, color, 1.0);
}

void PrimitiveRenderer::DrawFilledEllipse(float cx, float cy, float rx, float ry, ALLEGRO_COLOR color) {
    al_draw_filled_ellipse(cx, cy, rx, ry, color);
}

void PrimitiveRenderer::DrawArc(float cx, float cy, float r, float start_theta, float end_theta, ALLEGRO_COLOR color) {
    al_draw_arc(cx, cy, r, start_theta, end_theta, color, 1.0);
}

void PrimitiveRenderer::FlipDisplay() {
    if (display_) {
        al_flip_display();
    }
}

void PrimitiveRenderer::DrawLineIncremental(float x1, float y1, float x2, float y2, ALLEGRO_COLOR color, float lineWidth) {
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
    } else {
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

void PrimitiveRenderer::DrawPolyline(const std::vector<Point2D>& points, ALLEGRO_COLOR color, float lineWidth) {
    if (points.size() < 2) {
        return; // Linia łamana musi mieć co najmniej 2 punkty
    }

    for (size_t i = 0; i < points.size() - 1; ++i) {
        DrawLineIncremental(points[i].GetX(), points[i].GetY(), points[i + 1].GetX(), points[i + 1].GetY(), color, lineWidth);
    }
}

void PrimitiveRenderer::DrawPolyline(const std::vector<LineSegment>& lineSegments, ALLEGRO_COLOR color, float lineWidth) {
    for (const LineSegment& segment : lineSegments) {
        DrawLineIncremental(segment.GetStart().GetX(), segment.GetStart().GetY(), segment.GetEnd().GetX(), segment.GetEnd().GetY(), color, lineWidth);
    }
}