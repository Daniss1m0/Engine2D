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
	SpriteObject::~SpriteObject() {
		if (anim) {
			for (int i = 0; i < maxFrame; ++i) {
				if (anim[i]) {
					al_destroy_bitmap(anim[i]);
				}
			}
			delete[] anim;
		}
	}
	void SpriteObject::Animate() {
		if (maxFrame > 0) {
			if (++frameCount >= frameDelay) {
				frameCount = 0;
				if (++currentFrame >= maxFrame) {
					currentFrame = 0;
				}
			}
		}
	}
	void SpriteObject::Draw() {
		if (maxFrame > 0 && anim && anim[currentFrame])
				al_draw_scaled_rotated_bitmap(anim[currentFrame], al_get_bitmap_width(anim[currentFrame]) / 2.0, al_get_bitmap_height(anim[currentFrame]) / 2.0, _pos.x, _pos.y, _scale, _scale, _orientation, 0);
		else
				std::cerr << "Bitmap nie zainicjowany." << std::endl;
	}
	void SpriteObject::SetSprite(const char* spriteFilename, short int frameIndex) {
		if (!anim || frameIndex >= maxFrame) {
			ALLEGRO_BITMAP** newArray = new ALLEGRO_BITMAP * [frameIndex + 1];
			for (int i = 0; i < maxFrame; ++i) {
				newArray[i] = anim[i];
			}
			for (int i = maxFrame; i <= frameIndex; ++i) {
				newArray[i] = nullptr;
			}
			delete[] anim;
			anim = newArray;
			maxFrame = frameIndex + 1;
		}

		if (frameIndex < 0 || frameIndex >= maxFrame) {
			std::cerr << "Nieprawidlowy indeks: " << frameIndex << std::endl;
			return;
		}

		if (anim[frameIndex])
			al_destroy_bitmap(anim[frameIndex]);

		anim[frameIndex] = al_load_bitmap(spriteFilename);
		if (!anim[frameIndex]) {
			std::cerr << "Nie udalo sie zalodowac! " << spriteFilename << std::endl;
			exit(1);
		}
	}
	void SpriteObject::Move(const Vector2& vec) {
		_pos = _pos + vec;
	}
}