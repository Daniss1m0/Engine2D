#pragma once

#include "vector2.h"
#include "bitmapHandler.h"
#include "primitiveRenderer.h"

namespace game
{

	class GameObject
	{
	public:
		GameObject() = default;
		virtual ~GameObject() {}
		PrimitiveRenderer& renderer = PrimitiveRenderer::getInstance();
	};


	class DrawableObject : public GameObject
	{
	public:
		DrawableObject() = default;

		virtual void Draw() = 0;

		bool LoadFromFile(const char* filename);

	protected:
		BitmapHandler _handler;
		Vector2 _pos = { 0.0f, 0.0f };
	};


	class GeometryObject : public GameObject
	{
	public:
		GeometryObject() = default;

		GeometryObject(Vector2 pos,std::vector<Point2D>& polygon)
		{
			_pos = pos;
			_polygon = polygon;

			int i = 0;
			for (Point2D& point : polygon) {
				_points[i] = point + _pos;
				i++;
			}

		}

		virtual void Draw() = 0;
		virtual void SetThickness(float thickness) = 0;
		virtual void SetColor(ALLEGRO_COLOR color) = 0;

	protected:
		Vector2 _pos = { 0.0f, 0.0f };
		std::vector<Point2D> _points;
		std::vector<Point2D> _polygon;
		float _thickness = 1;
		ALLEGRO_COLOR _color = al_map_rgb(100, 100, 100);
	};


	class TransformableObject : public DrawableObject
	{
	public:
		TransformableObject() = default;

		TransformableObject(Vector2 pos, std::vector<Point2D>& polygon)
		{
			_pos = pos;
			_polygon = polygon;
			_scale = 1;

			for (Point2D& point : polygon) {
				_points.push_back(point + _pos);
			}
		}

		virtual void Move(const Vector2&) = 0;
		virtual void Rotate(float degrees) = 0;
		virtual void Scale(float scaleNumber) = 0;

	protected:
		Vector2 _pos = { 0.0f, 0.0f };
		std::vector<Point2D> _points;
		std::vector<Point2D> _polygon;
		float _scale = 1;
		float _orientation = 0; // w k¹tach nie w radianach
		//float _thickness = 1;
		//ALLEGRO_COLOR _color = al_map_rgb(100, 100, 100);
	};

	class Player : public DrawableObject, public TransformableObject
	{
	public:
		Player() = default;

		virtual void Draw();
		virtual void Move(const Vector2& vec);
	};

}