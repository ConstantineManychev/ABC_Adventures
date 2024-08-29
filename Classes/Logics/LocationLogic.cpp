#include "LocationLogic.h"

#include "Managers/ViewManager.h"
#include "Managers/DataManager.h"
#include "Managers/GameDirector.h"

_USEC

static const int TAIL_TAG = 99;

LocationLogic::LocationLogic()
	: mTaleParticles(nullptr)
	, mPlayer(nullptr)
{
}

LocationLogic::~LocationLogic()
{
	GD->setLocation(nullptr);
	GD->setPlayer(nullptr);
}

void LocationLogic::onOpen()
{
	GD->setPlayer(mPlayer);
}
	

void LocationLogic::onButtonTouchEvent(Ref* aSender, Touch* aTouch, ui::Widget::TouchEventType aEventType)
{
	Node* node = dynamic_cast<Node*>(aSender);

	if (node)
	{
		switch (aEventType)
		{
			case ui::Widget::TouchEventType::BEGAN:
			{
				onButtonTouchBegin(node, aTouch);
				break;
			}
			case ui::Widget::TouchEventType::CANCELED:
			{
				onButtonTouchCanceled(node, aTouch);
				break;
			}
			case ui::Widget::TouchEventType::ENDED:
			{
				onButtonTouchFinish(node, aTouch);
				break;
			}
			case ui::Widget::TouchEventType::MOVED:
			{
				onButtonTouchMove(node, aTouch);
				break;
			}
		}
	}
}

void LocationLogic::onButtonTouchBegin(Node* aNode, Touch* aTouch)
{
	VM->runActionForNode(aNode, "onBtnClickDown");

	std::string particlePath;
	const auto& path = DM->getGlobalValue("tale_paticle_path");
	if (path.isString())
	{
		particlePath = path.getString();
	}

	mTaleParticles = ParticleSystemQuad::create(particlePath);

	if (mTaleParticles)
	{
		mTaleParticles->setLocalZOrder(1000);
		mTaleParticles->setTag(TAIL_TAG);
		mTaleParticles->setPosition(aNode->convertToNodeSpace(aTouch->getLocation()));
		aNode->addChild(mTaleParticles);
	}
}

void LocationLogic::onButtonTouchFinish(Node* aNode, Touch* aTouch)
{
	VM->runActionForNode(aNode, "onBtnClickUp");

	float delayTime = mTaleParticles->getLife();
	auto delay = DelayTime::create(delayTime);

	Node* taleNode = mTaleParticles;

	auto removeParticles = CallFunc::create([=]()
	{
		aNode->removeChild(taleNode);

		auto child = aNode->getChildByTag(TAIL_TAG);
		if (!child)
		{
			mTaleParticles = nullptr;
		}
	});

	auto sequence = Sequence::create(delay, removeParticles, nullptr);
	sequence->setTag(TAIL_TAG);

	mTaleParticles->stop();
	aNode->runAction(sequence);
}

void LocationLogic::onButtonTouchCanceled(Node* aNode, Touch* aTouch)
{
	VM->runActionForNode(aNode, "onBtnClickCanceled");
}

void LocationLogic::onButtonTouchMove(Node* aNode, Touch* aTouch)
{
	VM->runActionForNode(aNode, "onBtnClickMove");

	mTaleParticles->setPosition(aNode->convertToNodeSpace(aTouch->getLocation()));
}

void LocationLogic::onKeyDown(Ref* aSender, EventKeyboard::KeyCode aKeyCode)
{
	Node* node = dynamic_cast<Node*>(aSender);

	if (mPlayer)
	{
		if (aKeyCode == DM->getKey("left"))
		{
			mPlayer->stopAllActions();
			auto repeatForeverAction = RepeatForever::create( MoveBy::create(1.f,Vec2(10.f, 0.f) ) );

			mPlayer->runAction(repeatForeverAction);

			mPlayer->setForceX(-500.f);
		}
		else if (aKeyCode == DM->getKey("right"))
		{
			mPlayer->stopAllActions();
			//auto repeatForeverAction = RepeatForever::create(MoveBy::create(-1.f, Vec2(10.f, 0.f)));

			//mPlayer->runAction(repeatForeverAction);

			mPlayer->setForceX(500.f);
		}
	}
}

void LocationLogic::onKeyUp(Ref* aSender, EventKeyboard::KeyCode aKeyCode)
{
	Node* node = dynamic_cast<Node*>(aSender);

	if (mPlayer)
	{
		mPlayer->setForceX(0.f);
	}
}

void LocationLogic::setupPlayer(Node* aNode)
{
	if (aNode)
	{
		mPlayer = dynamic_cast<Player*>(aNode);
	}
}