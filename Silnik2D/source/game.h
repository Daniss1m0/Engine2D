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


	class DrawableObject : virtual public GameObject
	{
	public:
		DrawableObject() = default;

		virtual void Draw() = 0;
		void SetOrientation(float degrees);
		void SetScale(float scale);

		bool LoadFromFile(const char* filename);

	protected:
		BitmapHandler _handler;
		Vector2 _pos = { 0.0f, 0.0f };
		float _scale=1;
		float _orientation=0;
	};


	class GeometryObject : virtual public GameObject
	{
	public:
		GeometryObject() = default;

		GeometryObject(Vector2 pos,std::vector<Point2D>& polygon)
		{
			_pos = pos;
			_polygon = polygon;

			for (Point2D& point : polygon) {
				_points.push_back(point + _pos);
			}
		}

		void Draw();
		void SetThickness(float thickness);
		void SetColor(ALLEGRO_COLOR color);

	protected:
		Vector2 _pos = { 0.0f, 0.0f };
		std::vector<Point2D> _points;
		std::vector<Point2D> _polygon;
		float _thickness = 1;
		ALLEGRO_COLOR _color = al_map_rgb(100, 100, 100);
	};


	class TransformableObject : virtual public GameObject
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

		void Move(const Vector2&);
		void Rotate(float degrees);
		void Scale(float scaleNumber);

	protected:
		Vector2 _pos = { 0.0f, 0.0f };
		std::vector<Point2D> _points;
		std::vector<Point2D> _polygon;
		float _scale = 1;
		float _orientation = 0; // w k¹tach nie w radianach
		//float _thickness = 1;
		//ALLEGRO_COLOR _color = al_map_rgb(100, 100, 100);
	};

	class Player : public DrawableObject
	{
	public:
		Player() = default;

		void Draw();
		void Move(const Vector2& vec);
	};

	class Polygon :public GeometryObject, public TransformableObject
	{
	public:
		Polygon() = default;

		Polygon(Vector2 pos, std::vector<Point2D>& polygon)
		{
			_pos = pos;
			_polygon = polygon;
			_scale = 1;

			for (Point2D& point : polygon) {
				_points.push_back(point + _pos);
			}
		}
		void Draw();
		void Rotate(float degrees);
		void Scale(float scaleNumber);

	protected:
		Vector2 _pos = { 0.0f, 0.0f };
		std::vector<Point2D> _points;
		std::vector<Point2D> _polygon;
		float _scale = 1;
		float _orientation = 0;
	};

}