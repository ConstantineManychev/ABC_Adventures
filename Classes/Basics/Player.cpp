#include "Player.h"

_USEC

Player* Player::create()
{
	Player* ret = new (std::nothrow) Player();
	if (ret && ret->init())
	{
		ret->autorelease();
		return ret;
	}
	else
	{
		delete ret;
		return nullptr;
	}
}