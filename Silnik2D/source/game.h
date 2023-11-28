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

	class AnimatedObject 
	{
	public:
		AnimatedObject() = default;
		virtual ~AnimatedObject() {}

		virtual void Animate() = 0;
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

		void Set_pos(Vector2 pos);
		void Set_points(std::vector<Point2D> points);
		void Set_polygon(std::vector<Point2D> polygon);
		void Set_thickness(float thickness);
		void Set_color(ALLEGRO_COLOR color);

		Vector2 Get_pos();
		std::vector<Point2D> Get_points();
		std::vector<Point2D> Get_polygon();
		float Get_thickness();
		ALLEGRO_COLOR Get_color();

		void Draw();

	protected:
		Vector2 _pos = { 0.0f, 0.0f };
		std::vector<Point2D> _points;
		std::vector<Point2D> _polygon;
		float _thickness = 1;
		ALLEGRO_COLOR _color = al_map_rgb(100, 100, 100);
	};


	class TransformableObject : public GeometryObject
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
		float _scale = 1;
		float _orientation = 0; // w k№tach nie w radianach
		//float _thickness = 1;
		//ALLEGRO_COLOR _color = al_map_rgb(100, 100, 100);
	};

	class SpriteObject : public DrawableObject, public AnimatedObject {
	private:
		short int maxFrame = 4;
		ALLEGRO_BITMAP** anim;
		int currentFrame;  // Добавляем переменную для отслеживания текущего кадра
		int frameCount;
		int frameDelay;

	public:
		SpriteObject() : anim(nullptr), currentFrame(0), frameCount(0), frameDelay(5) {}

		~SpriteObject() {
			if (anim) {
				for (int i = 0; i < maxFrame; ++i) {
					if (anim[i]) {
						al_destroy_bitmap(anim[i]);
					}
				}
				delete[] anim;
			}
		}

		void Draw() override {
			if (anim[currentFrame]) {
				_handler.Draw(_pos.x, _pos.y, _orientation, _scale);
			}
		}

		void Animate() override {
			if (++frameCount >= frameDelay) {
				frameCount = 0;
				if (++currentFrame >= maxFrame) {
					currentFrame = 0;
				}
			}
		}

		void SetSprite(const char* spriteFilename, short int frameIndex) {
			if (!anim) {
				anim = new ALLEGRO_BITMAP * [maxFrame];
				for (int i = 0; i < maxFrame; ++i) {
					anim[i] = nullptr;
				}
			}

			if (frameIndex < 0 || frameIndex >= maxFrame) {
				std::cerr << "Invalid frame index: " << frameIndex << std::endl;
				return;
			}

			if (anim[frameIndex]) {
				al_destroy_bitmap(anim[frameIndex]);
			}

			anim[frameIndex] = al_load_bitmap(spriteFilename);
			if (!anim[frameIndex]) {
				// Обработка ошибки загрузки изображения
				std::cerr << "Failed to load sprite: " << spriteFilename << std::endl;
				exit(1);
			}
		}

		void Move(const Vector2& vec) {
			_pos = _pos + vec;
		}
	};

	class Player : public SpriteObject
	{
	public:
		Player() = default;

		void Draw();
		void Move(const Vector2& vec);
	};

	class Polygon : public TransformableObject
	{
	public:
		Polygon(Vector2 pos, std::vector<Point2D>& polygon) : TransformableObject(pos, polygon) {}
	};

}