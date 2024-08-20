#ifndef __LOCATION_LOGIC_H__
#define __LOCATION_LOGIC_H__

#include "cocos2d.h"
#include "ui/UIWidget.h"

#include "CommonDefines.h"

_CSTART

class LocationLogic
{
private:

	virtual void onButtonTouchBegin(Node* aNode);
	virtual void onButtonTouchFinish(Node* aNode);
	virtual void onButtonTouchCanceled(Node* aNode);
	virtual void onButtonTouchMove(Node* aNode);

public:
	void onButtonTouchEvent(Ref* aSender, ui::Widget::TouchEventType aEventType);
};

_CEND

#endif // __LOCATION_LOGIC_H__
