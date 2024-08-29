#include "BaseBeing.h"

_USEC

BaseBeing::BaseBeing()
	: mMaxSpeed(1000.f)
	, mCurrentSpeed(0.f)
	, mCurrentForce(Vec2::ZERO)
{

}

BaseBeing::~BaseBeing()
{

}

BaseBeing* BaseBeing::create()
{
	BaseBeing* ret = new (std::nothrow) BaseBeing();
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

void BaseBeing::update(float delta)
{
	float maxSpeed = mMaxSpeed;

	if (mCurrentForce.x < 0)
	{
		maxSpeed = -maxSpeed;
	}
	else if (mCurrentForce.x == 0)
	{
		maxSpeed = 0;
	}

	if (mCurrentSpeed != maxSpeed)
	{
		float time = mCurrentForce.x == 0.f ? 1.f : (maxSpeed - mCurrentSpeed) / mCurrentForce.x;

		time = time <= delta ? time : delta;

		float distance = mCurrentSpeed * time + 0.5f * mCurrentForce.x * time * time;

		auto moveBy = MoveBy::create(time, Vec2(distance, 0));

		auto easeIn = EaseIn::create(moveBy, 2.f);

		mCurrentSpeed += mCurrentForce.x == 0.f ? -mCurrentSpeed : mCurrentForce.x * time;

		this->runAction(easeIn);
	}

	if (mCurrentSpeed == 0.f)
	{
		this->stopAllActions();
		this->unscheduleUpdate();
	}
	else if (mCurrentSpeed == maxSpeed)
	{
		auto moveConstant = MoveBy::create(delta, Vec2(maxSpeed * delta, 0));
		this->runAction(moveConstant);
	}
}

void BaseBeing::setMaxSpeed(float aSpeed)
{
	mMaxSpeed = aSpeed;
}

void BaseBeing::setForceX(float aForce)
{
	mCurrentForce.x = aForce;

	this->scheduleUpdate();
}

float BaseBeing::getSpeed()
{
	return mCurrentSpeed;
}
float BaseBeing::getMaxSpeed() 
{
	return mMaxSpeed;
}

float BaseBeing::getForceX()
{
	return mCurrentForce.x;
}