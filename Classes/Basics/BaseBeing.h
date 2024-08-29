#ifndef __BASE_BEING_H__
#define __BASE_BEING_H__

#include "cocos2d.h"

#include "CommonDefines.h"

_CSTART

class BaseBeing : public Sprite
{
public:

	BaseBeing();
	~BaseBeing();

	static BaseBeing* create();

	void setMaxSpeed(float aSpeed);

	void setForceX(float aForce);

	float getSpeed();
	float getMaxSpeed();

	float getForceX();

private:

	float mMaxSpeed;

	float mCurrentSpeed;
	Vec2 mCurrentForce;

	void update(float delta) override;

};

_CEND

#endif // __BASE_BEING_H__
