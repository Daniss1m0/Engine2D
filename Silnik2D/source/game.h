#pragma once

#include "vector2.h"
#include "bitmapHandler.h"

namespace game
{

	class GameObject
	{
	public:
		GameObject() = default;
		virtual ~GameObject() {}
	};

	class DrawableObject : public GameObject
	{
	public:
		DrawableObject() = default;

		virtual void Draw() = 0;
		
		bool LoadFromFile(const char* filename);

	protected:
		BitmapHandler _handler;
	};

	class TransformableObject : public GameObject
	{
	public:
		TransformableObject() = default;

		virtual void Move(const Vector2&) = 0;

	protected:
		Vector2 _pos = { 0.0f, 0.0f };
	};

	class Player : public DrawableObject, public TransformableObject
	{
	public:
		Player() = default;

		virtual void Draw();
		virtual void Move(const Vector2& vec);
	};

}