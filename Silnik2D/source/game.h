#pragma once

#include "vector2.h"
#include "bitmapHandler.h"
#include "primitiveRenderer.h"

namespace game
{
	class UpdatableObject
	{
	public:
		virtual void Update()
		{
			std::cout << "update" << std::endl;
		}

		//virtual void Draw(){}
		//virtual void Move(){}

		virtual ~UpdatableObject() {};
	};

	static std::vector<UpdatableObject*> UpdatableVector; // wektor wszystkich obiektow ktore sa updatowane z timer eventem
	

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


	class BitmapObject : virtual public GameObject
	{
	public:
		BitmapObject() = default;

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
		float _orientation = 0; // w k¹tach nie w radianach
		//float _thickness = 1;
		//ALLEGRO_COLOR _color = al_map_rgb(100, 100, 100);
	};

	class SpriteObject : public BitmapObject, public AnimatedObject,public UpdatableObject {
	public:
		//SpriteObject() : anim(nullptr), currentFrame(0), frameCount(0), frameDelay(5), maxFrame(0) {}
		SpriteObject()
		{
			UpdatableVector.push_back(this);
		}
		~SpriteObject();
		void Animate();
		void Draw();
		void SetSprite(const char* spriteFilename, short int frameIndex);
		void Move(const Vector2& vec);
		void Update();
	private:
		ALLEGRO_BITMAP** anim=nullptr;
		int currentFrame=0;
		int frameCount=0;
		int frameDelay=5;
		short int maxFrame=0;
	};

	class Player : public SpriteObject
	{
	public:
		//Player() = default;

		Player()
		{
			UpdatableVector.push_back(this);
		}

		void Draw();
		void Move(const Vector2& vec);
		void Update();
		void Shoot();
	};

	class Polygon : public TransformableObject
	{
	public:
		Polygon(Vector2 pos, std::vector<Point2D>& polygon) : TransformableObject(pos, polygon) {}
	};

	//a

	class test :public UpdatableObject
	{
	public:
		test()
		{
			UpdatableVector.push_back(this);
		}

		void Update();

	protected:
		int _nic = 0;
	};

	class AllegroPrimitivesFilledCircleObject :virtual public GameObject,public UpdatableObject
	{
	public:
		AllegroPrimitivesFilledCircleObject() = default;
		AllegroPrimitivesFilledCircleObject(Vector2 pos, float radius, ALLEGRO_COLOR color)
		{
			_pos = pos;
			_radius = radius;
			_color = color;

			UpdatableVector.push_back(this);
		}

		void Draw();
		void Update();

		~AllegroPrimitivesFilledCircleObject(){}

		Vector2 _pos = { 0.0f,0.0f };
		float _radius;
		ALLEGRO_COLOR _color= al_map_rgb(255, 0, 0);
	};

	class MovingFilledCircleObject : public AllegroPrimitivesFilledCircleObject
	{
	public:
		MovingFilledCircleObject() = default;
		MovingFilledCircleObject(Vector2 pos, float radius, ALLEGRO_COLOR color, Vector2 velocity)
		{
			_pos = pos;
			_radius = radius;
			_color = color;
			_velocity = velocity;

			UpdatableVector.push_back(this);
		}

		void Update();

	protected:
		Vector2 _velocity = { 0.0f,0.0f };
	};

	static std::vector<MovingFilledCircleObject*> EnemyVector;
	class Enemy :public MovingFilledCircleObject
	{
	public:
		Enemy(Vector2 pos, float radius, ALLEGRO_COLOR color, Vector2 velocity)
		{
			_pos = pos;
			_radius = radius;
			_color = color;
			_velocity = velocity;

			UpdatableVector.push_back(this);
			EnemyVector.push_back(this);
		}
	};
	


	//static std::vector<Projectile*> ProjectileVector;
	class Projectile : public MovingFilledCircleObject
	{
	public:
		Projectile(Vector2 pos, float radius, ALLEGRO_COLOR color, Vector2 velocity)
		{
			_pos = pos;
			_radius = radius;
			_color = color;
			_velocity = velocity;

			UpdatableVector.push_back(this);
			//ProjectileVector.push_back(this);
			std::cout << "projectile created" << std::endl;
		}
		~Projectile()
		{
			std::cout << "projectile being deleted" << std::endl;
		}

		void Update();
	};

}