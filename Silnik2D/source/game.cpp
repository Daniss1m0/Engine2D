#include "game.h"

namespace game
{

	void RotatePoint(Point2D& point, float angle) { // angle w katach nie w radianach
		angle = angle * 3.14159/180.0;
		double x = point.GetX() * cos(angle) - point.GetY() * sin(angle);
		double y = point.GetX() * sin(angle) + point.GetY() * cos(angle);

		point.SetX(x);
		point.SetY(y);
	}

	void Player::Draw()
	{
		_handler.Draw(_pos.x, _pos.y, _orientation,_scale);
	}

	void Player::Move(const Vector2& vec)
	{
		_pos =_pos+ vec;
	}

	bool DrawableObject::LoadFromFile(const char* filename)
	{
		return _handler.LoadFromFile(filename);
	}

	void DrawableObject::Draw()
	{
		_handler.Draw(_pos.x, _pos.y, _orientation, _scale);
	}

	void DrawableObject::SetOrientation(float orientation)
	{
		_orientation = orientation;
	}

	void DrawableObject::SetScale(float scale)
	{
		_scale = scale;
	}

	// GEOMETRY OBJECT
	void GeometryObject::Draw()
	{
		renderer.DrawClosedPolygon(_points, _color, _thickness);
	}

		// SETTERY
	void GeometryObject::Set_pos(Vector2 pos)
	{
		_pos = pos;
	}

	void GeometryObject::Set_points(std::vector<Point2D> points)
	{
		_points = points;
	}

	void GeometryObject::Set_polygon(std::vector<Point2D> polygon)
	{
		_polygon = polygon;
	}

	void GeometryObject::Set_thickness(float thickness)
	{
		_thickness = thickness;
	}

	void GeometryObject::Set_color(ALLEGRO_COLOR color)
	{
		_color = color;
	}

		// GETTERY
	Vector2 GeometryObject::Get_pos()
	{
		return _pos;
	}

	std::vector<Point2D> GeometryObject::Get_points()
	{
		return _points;
	}

	std::vector<Point2D> GeometryObject::Get_polygon()
	{
		return _polygon;
	}

	float GeometryObject::Get_thickness()
	{
		return _thickness;
	}

	ALLEGRO_COLOR GeometryObject::Get_color()
	{
		return _color;
	}

	// TRANSFORMABLE OBJECT
	void TransformableObject::Move(const Vector2& vec)
	{
		for(Point2D& point : _points)
		{
			point = point + vec;
		}
	}

	void TransformableObject::Rotate(float degrees)
	{
		_orientation = degrees;
		for (Point2D& point : _polygon)
		{
			RotatePoint(point, degrees);
		}

		int i = 0;
		for (Point2D& point : _polygon) {
			_points[i] = point + _pos;
			i++;
		}
	}

	void TransformableObject::Scale(float scale)
	{
		float scaleMultiplier = scale / _scale;
		_scale = scale;

		for (Point2D& point : _polygon)
		{
			point = point * scaleMultiplier;
		}

		int i = 0;
		for (Point2D& point : _polygon) {
			_points[i] = point + _pos;
			i++;
		}

	}
}