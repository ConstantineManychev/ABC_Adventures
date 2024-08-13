#include "NodeHelper.h"


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

	return result;
}