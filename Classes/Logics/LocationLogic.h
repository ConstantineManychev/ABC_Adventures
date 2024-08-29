#ifndef __LOCATION_LOGIC_H__
#define __LOCATION_LOGIC_H__

#include "cocos2d.h"
#include "ui/UIWidget.h"

#include "Basics/Player.h"

#include "CommonDefines.h"

_CSTART

class LocationLogic
{
private:

	ParticleSystemQuad* mTaleParticles;
	Player* mPlayer;

	virtual void onButtonTouchBegin(Node* aNode, Touch* aTouch);
	virtual void onButtonTouchFinish(Node* aNode, Touch* aTouch);
	virtual void onButtonTouchCanceled(Node* aNode, Touch* aTouch);
	virtual void onButtonTouchMove(Node* aNode, Touch* aTouch);

protected:

	virtual void onKeyDown(Ref* aSender, EventKeyboard::KeyCode aKeyCode);
	virtual void onKeyUp(Ref* aSender, EventKeyboard::KeyCode aKeyCode);

public:

	void onButtonTouchEvent(Ref* aSender, Touch* touch, ui::Widget::TouchEventType aEventType);
	void setupPlayer(Node* aNode);

	virtual void onOpen();

	LocationLogic();
	~LocationLogic();
};

_CEND

#endif // __LOCATION_LOGIC_H__
