#include "PrimitiveRenderer.h"
#define M_PI 3.14159265358979323846

Point2D::Point2D(float x, float y) : _x(x), _y(y) {
}

float Point2D::GetX() const {
    return _x;
}

float Point2D::GetY() const {
    return _y;
}

void Point2D::SetX(float x) {
    _x = x;
}

void Point2D::SetY(float y) {
    _y = y;
}

void Point2D::SetPosition(float x, float y) {
    _x = x;
    _y = y;
}

/*void Point2D::Draw(PrimitiveRenderer& renderer, ALLEGRO_COLOR color, float pointSize) {
    renderer.DrawFilledCircle(x_, y_, pointSize, color);
}*/

LineSegment::LineSegment(Point2D start, Point2D end) : _start(start), _end(end) {}

const Point2D& LineSegment::GetStartPoint() const
{
	return _start;
}

const Point2D& LineSegment::GetEndPoint() const
{
	return _end;
}

void LineSegment::SetStartPoint(Point2D start)
{
	_start = start;
}

void LineSegment::SetEndPoint(Point2D end)
{
	_end = end;
}

void LineSegment::Draw(PrimitiveRenderer& renderer, const ALLEGRO_COLOR& color, float thickness, bool additive)
{
	if (additive) {
		renderer.DrawLineIncremental(_start, _end, color, thickness);
	}
	else {
		renderer.DrawLine(_start, _end, color, thickness);
	}
}

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

void PrimitiveRenderer::DrawPixel(Point2D point, const ALLEGRO_COLOR& color) {
    al_draw_pixel(point.GetX(), point.GetY(), color);
}

void PrimitiveRenderer::DrawLine(Point2D start, Point2D end, const ALLEGRO_COLOR& color, float thickness) {
    al_draw_line(start.GetX(), start.GetY(), end.GetX(), end.GetY(), color, thickness);
}

void PrimitiveRenderer::DrawTriangle(Point2D point1, Point2D point2, Point2D point3, const ALLEGRO_COLOR& color) {
    al_draw_triangle(point1.GetX(), point1.GetY(), point2.GetX(), point2.GetY(), point3.GetX(), point3.GetY(), color, 1.0f);
}

void PrimitiveRenderer::DrawFilledTriangle(Point2D point1, Point2D point2, Point2D point3, const ALLEGRO_COLOR& color) {
    al_draw_filled_triangle(point1.GetX(), point1.GetY(), point2.GetX(), point2.GetY(), point3.GetX(), point3.GetY(), color);
}

void PrimitiveRenderer::DrawRectangle(Point2D point, float width, float height, const ALLEGRO_COLOR& color) {
    al_draw_rectangle(point.GetX(), point.GetY(), point.GetX() + width, point.GetY() + height, color, 1.0f);
}

void PrimitiveRenderer::DrawFilledRectangle(Point2D point, float width, float height, const ALLEGRO_COLOR& color) {
    al_draw_filled_rectangle(point.GetX(), point.GetY(), point.GetX() + width, point.GetY() + height, color);
}

void PrimitiveRenderer::DrawRoundedRectangle(Point2D point, float width, float height, float rx, float ry, const ALLEGRO_COLOR& color) {
    al_draw_rounded_rectangle(point.GetX(), point.GetY(), point.GetX() + width, point.GetY() + height, rx, ry, color, 1.0f);
}

void PrimitiveRenderer::DrawFilledRoundedRectangle(Point2D point, float width, float height, float rx, float ry, const ALLEGRO_COLOR& color) {
    al_draw_filled_rounded_rectangle(point.GetX(), point.GetY(), point.GetX() + width, point.GetY() + height, rx, ry, color);
}

void PrimitiveRenderer::DrawCircle(Point2D point, float radius, const ALLEGRO_COLOR& color) {
    al_draw_circle(point.GetX(), point.GetY(), radius, color, 1.0);
}

void PrimitiveRenderer::DrawCircleSymmetry4(Point2D p, float radius, ALLEGRO_COLOR color) {
    float x, y;

    for (float alpha = 0; alpha <= M_PI / 2; alpha += 0.01) {
        x = radius * cos(alpha);
        y = radius * sin(alpha);

        al_draw_pixel(p.GetX() + x, p.GetY() + y, color);

        al_draw_pixel(p.GetX() + x, p.GetY() - y, color);

        al_draw_pixel(p.GetX() - x, p.GetY() + y, color);
        al_draw_pixel(p.GetX() - x, p.GetY() - y, color);
    }
}

void PrimitiveRenderer::DrawFilledCircle(Point2D point, float radius, const ALLEGRO_COLOR& color) {
    al_draw_filled_circle(point.GetX(), point.GetY(), radius, color);
}

void PrimitiveRenderer::DrawEllipse(Point2D point, float rx, float ry, const ALLEGRO_COLOR& color) {
    al_draw_ellipse(point.GetX(), point.GetY(), rx, ry, color, 1.0);
}

void PrimitiveRenderer::DrawEllipseSymmetry4(Point2D p, float rx, float ry, const ALLEGRO_COLOR& color) {
    float x, y;

    for (float alpha = 0; alpha <= M_PI / 2; alpha += 0.01) {
        x = rx * cos(alpha);
        y = ry * sin(alpha);

        al_draw_pixel(p.GetX() + x, p.GetY() + y, color);

        al_draw_pixel(p.GetX() + x, p.GetY() - y, color);

        al_draw_pixel(p.GetX() - x, p.GetY() + y, color);
        al_draw_pixel(p.GetX() - x, p.GetY() - y, color);
    }
}

void PrimitiveRenderer::DrawFilledEllipse(Point2D point, float rx, float ry, const ALLEGRO_COLOR& color) {
    al_draw_filled_ellipse(point.GetX(), point.GetY(), rx, ry, color);
}

void PrimitiveRenderer::DrawArc(Point2D point, float r, float start_theta, float end_theta, const ALLEGRO_COLOR& color) {
    al_draw_arc(point.GetX(), point.GetY(), r, start_theta, end_theta, color, 1.0f);
}

void PrimitiveRenderer::DrawClosedPolygon(const std::vector<Point2D>& points, const ALLEGRO_COLOR& color, float thickness) {
    size_t numPoints = points.size();

    if (numPoints < 3) {
        std::cerr << "Nie udało się zrobić wielokąta." << std::endl;
        return;
    }

    for (size_t i = 0; i < numPoints - 1; ++i) {
        DrawLine(points[i], points[i + 1], color, thickness);
    }
    DrawLine(points.back(), points.front(), color, thickness);
}


void PrimitiveRenderer::FlipDisplay() {
    if (_display) {
        al_flip_display();
    }
}

void PrimitiveRenderer::DrawLineIncremental(Point2D start, Point2D end, const ALLEGRO_COLOR& color, float lineWidth) {
    float dx = fabs(end.GetX() - start.GetX());
    float dy = fabs(end.GetY() - start.GetY());
    float x = start.GetX();
    float y = start.GetY();
    float sx = (start.GetX() < end.GetX()) ? 1.0f : -1.0f;
    float sy = (start.GetY() < end.GetY()) ? 1.0f : -1.0f;

    if (dx > dy) {
        float error = dx / 2.0f;
        while (x != end.GetX()) {
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
        while (y != end.GetX()) {
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
        DrawLine(points[i], points[i + 1], color, lineWidth);
    }
}

void PrimitiveRenderer::DrawPolyline(const std::vector<LineSegment>& lineSegments, const ALLEGRO_COLOR& color, float lineWidth) {
    for (const LineSegment& segment : lineSegments) {
        DrawLine(segment.GetStartPoint(), segment.GetEndPoint(), color, lineWidth);
    }
}

std::vector<Point2D> PrimitiveRenderer::GenerateSquareSpiralPoints(float centerX, float centerY, int numTurns, float sideLength) {
    std::vector<Point2D> spiralPoints;

    float x = centerX;
    float y = centerY;
    spiralPoints.push_back(Point2D(x, y));
    x = x + sideLength;
    spiralPoints.push_back(Point2D(x,y));

    Vector2 lastVector(sideLength, 0.0f);
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

// Algorytm Boundary Fill
void PrimitiveRenderer::boundaryFill(int x, int y, const ALLEGRO_COLOR& fill_color, const ALLEGRO_COLOR& boundary_color) {
    // Pobierz kolor piksela P
    ALLEGRO_COLOR currentColor = al_get_pixel(al_get_target_bitmap(), x, y);

    // Jeśli kolor P jest równy kolorowi wypełnienia lub krawędzi, zakończ
    if (colorsAreEqual(currentColor, fill_color) || colorsAreEqual(currentColor, boundary_color)) {
        return;
    }

    // Ustaw kolor P na kolor wypełnienia
    al_put_pixel(x, y, fill_color);

    // Wywołaj rekurencyjnie boundary_fill dla sąsiednich pikseli
    boundaryFill(x + 1, y, fill_color, boundary_color); // prawy piksel
    boundaryFill(x - 1, y, fill_color, boundary_color); // lewy piksel
    boundaryFill(x, y + 1, fill_color, boundary_color); // dolny piksel
    boundaryFill(x, y - 1, fill_color, boundary_color); // górny piksel
}

// Algorytm Flood Fill
void PrimitiveRenderer::floodFill(int x, int y, const ALLEGRO_COLOR& fill_color, const ALLEGRO_COLOR& background_color) {
    // Pobierz kolor piksela P
    ALLEGRO_COLOR currentColor = al_get_pixel(al_get_target_bitmap(), x, y);

    // Jeśli kolor P jest równy kolorowi wypełnienia lub tła, zakończ
    if (colorsAreEqual(currentColor, fill_color) || !colorsAreEqual(currentColor, background_color)) {
        return;
    }

    // Ustaw kolor P na kolor wypełnienia
    al_put_pixel(x, y, fill_color);

    // Wykorzystaj stos do śledzenia pikseli do sprawdzenia
    std::stack<Point2D> pixelsToCheck;
    pixelsToCheck.push(Point2D(x, y));

    while (!pixelsToCheck.empty()) {
        // Pobierz współrzędne piksela z wierzchołka stosu
        Point2D currentPoint = pixelsToCheck.top();
        pixelsToCheck.pop();

        // Sprawdź sąsiednie piksele i dodaj do stosu te, które trzeba sprawdzić
        checkAndAddPixel(pixelsToCheck, Point2D(currentPoint.GetX() + 1, currentPoint.GetY()), fill_color, background_color); // prawy piksel
        checkAndAddPixel(pixelsToCheck, Point2D(currentPoint.GetX() - 1, currentPoint.GetY()), fill_color, background_color); // lewy piksel
        checkAndAddPixel(pixelsToCheck, Point2D(currentPoint.GetX(), currentPoint.GetY() + 1), fill_color, background_color); // dolny piksel
        checkAndAddPixel(pixelsToCheck, Point2D(currentPoint.GetX(), currentPoint.GetY() - 1), fill_color, background_color); // górny piksel
    }
}

bool PrimitiveRenderer::colorsAreEqual(const ALLEGRO_COLOR& color1, const ALLEGRO_COLOR& color2) {
    return color1.r == color2.r && color1.g == color2.g && color1.b == color2.b && color1.a == color2.a;
}

// Funkcja pomocnicza do sprawdzenia i dodania piksela do stosu w algorytmie Flood Fill
void PrimitiveRenderer::checkAndAddPixel(std::stack<Point2D>& pixelsToCheck, const Point2D& point, const ALLEGRO_COLOR& fillColor, const ALLEGRO_COLOR& backgroundColor) {
    // Pobierz kolor piksela
    ALLEGRO_COLOR currentColor = al_get_pixel(al_get_target_bitmap(), point.GetX(), point.GetY());

    // Jeśli kolor piksela jest równy kolorowi tła, ustaw go na kolor wypełnienia i dodaj do stosu
    if (colorsAreEqual(currentColor, backgroundColor)) {
        al_put_pixel(point.GetX(), point.GetY(), fillColor);
        pixelsToCheck.push(point);
    }
}