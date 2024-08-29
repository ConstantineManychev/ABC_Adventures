#include "BaseLocation.h"

#include "Managers/GameDirector.h"

_USEC

BaseLocation* BaseLocation::create()
{
	BaseLocation* ret = new (std::nothrow) BaseLocation();
	if (ret && ret->init())
	{
		ret->autorelease();
		ret->setupGlobalTouchListener();
		ret->setupGlobalKeyListener();
		return ret;
	}
	else
	{
		delete ret;
		return nullptr;
	}
}

void BaseLocation::onOpen()
{
	Parent::onOpen();
	GD->setLocation(this);
}

void BaseLocation::setupGlobalTouchListener()
{
	auto touchListener = EventListenerTouchAllAtOnce::create();

	touchListener->onTouchesBegan = [this](const std::vector<Touch*>& touches, Event* event)
	{
		for (auto touch : touches)
		{
			this->onButtonTouchEvent(this, touch, ui::Widget::TouchEventType::BEGAN);
		}
		return true;
	};

	touchListener->onTouchesMoved = [this](const std::vector<Touch*>& touches, Event* event)
	{
		for (auto touch : touches)
		{
			this->onButtonTouchEvent(this, touch, ui::Widget::TouchEventType::MOVED);
		}
	};

	touchListener->onTouchesEnded = [this](const std::vector<Touch*>& touches, Event* event)
	{
		for (auto touch : touches)
		{
			this->onButtonTouchEvent(this, touch, ui::Widget::TouchEventType::ENDED);
		}
	};

	touchListener->onTouchesCancelled = [this](const std::vector<Touch*>& touches, Event* event)
	{
		for (auto touch : touches)
		{
			this->onButtonTouchEvent(this, touch, ui::Widget::TouchEventType::CANCELED);
		}
	};

	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);
}

void BaseLocation::setupGlobalKeyListener()
{
	auto listener = cocos2d::EventListenerKeyboard::create();

	listener->onKeyPressed = [this](cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event)
	{
		this->onKeyDown(this, keyCode);
	};

	listener->onKeyReleased = [this](cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event)
	{
		this->onKeyUp(this, keyCode);
	};

	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}
