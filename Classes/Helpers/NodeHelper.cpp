
#include "ui/UIButton.h"

#include "NodeHelper.h"
#include "Basics/BaseLocation.h"
#include "Logics/LocationLogic.h"


_USEC

Node* NodeHelper::createNodeForType(const std::string& aType)
{
	Node* result = nullptr;
	if (aType == "Node")
	{
		result = Node::create();
	}
	else if (aType == "Sprite")
	{
		result = Sprite::create();
	}
	else if (aType == "Button")
	{
		ui::Button* btn = ui::Button::create();

		result = btn;
	}
	else if (aType == "Location")
	{
		result = BaseLocation::create();
	}

	return result;
}