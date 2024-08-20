#include "LocationLogic.h"

#include "Managers/ViewManager.h"

_USEC

void LocationLogic::onButtonTouchEvent(Ref* aSender, ui::Widget::TouchEventType aEventType)
{
	Node* node = dynamic_cast<Node*>(aSender);

	if (node)
	{
		switch (aEventType)
		{
		case ui::Widget::TouchEventType::BEGAN:
		{
			onButtonTouchBegin(node);
			break;
		}
		case ui::Widget::TouchEventType::CANCELED:
		{
			onButtonTouchCanceled(node);
			break;
		}
		case ui::Widget::TouchEventType::ENDED:
		{
			onButtonTouchFinish(node);
			break;
		}
		case ui::Widget::TouchEventType::MOVED:
		{
			onButtonTouchMove(node);
			break;
		}
		}
	}
}

void LocationLogic::onButtonTouchBegin(Node* aNode)
{
	VM->runActionForNode(aNode, "onBtnClickDown");
}

void LocationLogic::onButtonTouchFinish(Node* aNode)
{
	VM->runActionForNode(aNode, "onBtnClickUp");
}

void LocationLogic::onButtonTouchCanceled(Node* aNode)
{
	VM->runActionForNode(aNode, "onBtnClickCanceled");
}

void LocationLogic::onButtonTouchMove(Node* aNode)
{
	VM->runActionForNode(aNode, "onBtnClickMove");
}