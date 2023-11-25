#include "game.h"

namespace game
{

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

}