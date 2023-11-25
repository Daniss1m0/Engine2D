#include "game.h"

namespace game
{

	void Player::Draw()
	{

	}

	void Player::Move(const Vector2& vec)
	{
		_pos += vec;
	}

}