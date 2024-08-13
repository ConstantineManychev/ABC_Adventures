#include "ViewManager.h"

#include "Helpers/JsonHelper.h"
#include "Helpers/NodeHelper.h"

#include "DataManager.h"

_USEC

ViewManager::ViewManager()
{

}

ViewManager* ViewManager::getInstance()
{
	static ViewManager instance;
	return &instance;
}

Node* ViewManager::createViewByID(const std::string& aID)
{
	Node* result = nullptr;
	const BValue& viewInfo = DM->getViewInfoByID(aID);

	result = createNodeFromBValue(viewInfo);

	result->setScale(DM->getScaleY());

	return result;
}

Node* ViewManager::createNodeFromBValue(const BValue& aBValue, Node* aParentNode)
{
	Node* result = nullptr;
	
	if (aBValue.isMap())
	{
		auto& valMap = aBValue.getValueMap();

		auto it = valMap.find("type");
		if ( it != valMap.end() &&  it->second.isString())
		{
			result = NodeHelper::createNodeForType(it->second.getString());
			
			if (result)
			{
				if (aParentNode)
				{
					result->setParent(aParentNode);
				}

				for (auto it = valMap.begin(); it != valMap.end(); ++it)
				{
					if (it->first == "children")
					{
						continue;
					}
					fillNodeParamFromBValue(result, it->first, it->second);
				}

				auto itChildren = valMap.find("children");
				if (itChildren != valMap.end())
				{
					fillNodeParamFromBValue(result, itChildren->first, itChildren->second);
				}

				if (aParentNode)
				{
					result->setParent(nullptr);
				}
			}
		}
	}

	return result;
}

void ViewManager::fillNodeParamFromBValue(Node* aNode, const std::string& aParamID, const BValue& aBValue)
{
	if (aNode)
	{
		auto valueType = aBValue.getType();

		switch (valueType)
		{
			case BValue::Type::MAP:
			{
				int type = 0;
				if (aParamID == "children")
				{
					type = 1;
				}
				else if (aParamID == "params")
				{
					type = 2;
				}

				auto& valMap = aBValue.getValueMap();

				for (auto it = valMap.begin(); it != valMap.end(); ++it)
				{
					switch (type)
					{
						case 1:
						{
							aNode->addChild(createNodeFromBValue(it->second, aNode));
							break;
						}
						case 2:
						{
							fillNodeParamFromBValue(aNode, it->first, it->second);
							break;
						}
						default:
						{
							break;
						}
					}
				}

				break;
			}
			case BValue::Type::VECTOR:
			{

				break;
			}
			case BValue::Type::STRING:
			{
				if (aParamID == "id")
				{
					aNode->setName(aBValue.getString());
				}
				else if (aParamID == "res")
				{
					auto sprite = dynamic_cast<Sprite*>(aNode);
					if (sprite)
					{
						sprite->initWithFile(aBValue.getString());
					}
				}

				break;
			}
			case BValue::Type::FLOAT:
			case BValue::Type::DOUBLE:
			{
				Size parentSize = Size::ZERO;

				auto parent = aNode->getParent();
				if (parent)
				{
					parentSize = parent->getContentSize();
				}
				else
				{
					parentSize = Director::getInstance()->getVisibleSize();
				}
				//Vec2 origin = Director::getInstance()->getVisibleOrigin();

				if (aParamID == "pos_x")
				{
					aNode->setPositionX(parentSize.width * aBValue.getFloat());// +origin.x);
				}
				else if (aParamID == "pos_y")
				{
					aNode->setPositionY(parentSize.height * aBValue.getFloat());// +origin.y);
				}
				else if (aParamID == "anch_x")
				{
					auto anch = aNode->getAnchorPoint();
					anch.x = aBValue.getFloat();
					aNode->setAnchorPoint(anch);
				}
				else if (aParamID == "anch_y")
				{
					auto anch = aNode->getAnchorPoint();
					anch.y = aBValue.getFloat();
					aNode->setAnchorPoint(anch);
				}
				break;
			}
			case BValue::Type::COLOR3B:
			{
				aNode->setColor(aBValue.getColor3B());
				break;
			}
			case BValue::Type::SIZE:
			{
				aNode->setContentSize(aBValue.getSize());
				break;
			}
			default:
			{
				break;
			}
		}
	}
}

void ViewManager::removeViewByID(const std::string& aID)
{
	auto it = mViews.find(aID);
	if (it != mViews.end())
	{
		mViews.erase(it);
	}
}

Node* ViewManager::getViewByID(const std::string& aID)
{
	Node* result = nullptr;

	auto it = mViews.find(aID);
	if (it != mViews.end())
	{
		result = it->second;
	}
	else
	{
		mViews[aID] = createViewByID(aID);
		result = mViews[aID];

	}

	return result;
}