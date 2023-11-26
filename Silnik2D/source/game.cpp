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
		_handler.Draw(_pos.x, _pos.y, _handler.GetWidth(), _handler.GetHeight());
	}

	void Player::Move(const Vector2& vec)
	{
		_pos += vec;
	}

	bool DrawableObject::LoadFromFile(const char* filename)
	{
		return _handler.LoadFromFile(filename);
	}

	void DrawableObject::Draw()
	{
		_handler.Draw(_pos.x, _pos.y, _handler.GetWidth(), _handler.GetHeight());
	}

	void GeometryObject::Draw()
	{
		renderer.DrawClosedPolygon(_points, _color, _thickness);
	}

	void GeometryObject::SetColor(ALLEGRO_COLOR color)
	{
		_color = color;
	}

	void GeometryObject::SetThickness(float thickness)
	{
		_thickness = thickness;
	}

	void TransformableObject::Move(const Vector2& vec)
	{
		for(Point2D& point : _points)
		{
			point = point + vec;
		}
	}

	void TransformableObject::Rotate(float degrees)
	{
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