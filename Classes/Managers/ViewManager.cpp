#include "ViewManager.h"

#include "ui/UIButton.h"

#include "Helpers/JsonHelper.h"
#include "Helpers/NodeHelper.h"

#include "DataManager.h"
#include "ScenesManager.h"

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

	if (result)
	{
		result->setScale(DM->getScaleY());
	}

	return result;
}

Node* ViewManager::createNodeFromBValue(const BValue& aBValue, Node* aParentNode)
{
	Node* result = nullptr;
	
	if (aBValue.isMap())
	{
		const auto& valMap = aBValue.getValueMap();

		auto it = valMap.find("type");
		if (it != valMap.end() && it->second.isString())
		{
			result = NodeHelper::createNodeForType(it->second.getString());
		}
			
		if (result)
		{
			auto itChildren = valMap.find("children");
			auto itActions = valMap.find("actions");

			if (aParentNode)
			{
				result->setParent(aParentNode);
			}

			std::string paramName;
			for (auto it = valMap.begin(); it != valMap.end(); ++it)
			{
				paramName = it->first;
				if (cExcludeParams.find(paramName) == cExcludeParams.end())
				{
					fillNodeParamFromBValue(result, paramName, it->second);
				}
			}

				
			if (itChildren != valMap.end())
			{
				fillNodeParamFromBValue(result, itChildren->first, itChildren->second);
			}

				
			if (itActions != valMap.end())
			{
				createActionFromBValue(itActions->second, result);
			}

			if (aParentNode)
			{
				result->setParent(nullptr);
			}

			//For first time just start every action
			//Need to make by listener and events
			runActionForNode(result, "onCreate");
			/*auto actionsListIt = mViewsActions.find(result);
			if (actionsListIt != mViewsActions.end())
			{
				auto& actionsList = actionsListIt->second;
				for (auto actionsVec = actionsList.begin(); actionsVec != actionsList.end(); ++actionsVec)
				{
					auto sequence = Sequence::create(actionsVec->second);

					result->runAction(sequence);
				}
			}*/
		}
	}

	return result;
}

void ViewManager::fillNodeParamFromBValue(Node* aNode, const std::string& aParamID, const BValue& aBValue)
{
	if (aNode)
	{
		auto itParam = cParamTypeMap.find(aParamID);
		Params paramType = (itParam != cParamTypeMap.end()) ? itParam->second : Params::NONE;

		auto valueType = aBValue.getType();

		switch (valueType)
		{
			case BValue::Type::MAP:
			{
				const auto& valMap = aBValue.getValueMap();

				for (auto it = valMap.begin(); it != valMap.end(); ++it)
				{
					switch (paramType)
					{
						case Params::CHILDREN:
						{
							aNode->addChild(createNodeFromBValue(it->second, aNode));
							break;
						}
						case Params::PARAMS:
						{
							fillNodeParamFromBValue(aNode, it->first, it->second);
							break;
						}
						case Params::ACTIONS:
						{
							createActionFromBValue(it->second, aNode);
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
				switch (paramType)
				{
					case Params::ID:
					{
						aNode->setName(aBValue.getString());
						break;
					}
					case Params::RES:
					{
						auto sprite = dynamic_cast<Sprite*>(aNode);
						if (sprite)
						{
							sprite->initWithFile(aBValue.getString());
						}
						break;
					}
					case Params::RES_NORMAL:
					{
						auto btn = dynamic_cast<ui::Button*>(aNode);
						if (btn)
						{
							btn->loadTextureNormal(aBValue.getString());
						}
						break;
					}
					case Params::RES_PRESSED:
					{
						auto btn = dynamic_cast<ui::Button*>(aNode);
						if (btn)
						{
							btn->loadTexturePressed(aBValue.getString());
						}
						break;
					}
					case Params::RES_DISABLE:
					{
						auto btn = dynamic_cast<ui::Button*>(aNode);
						if (btn)
						{
							btn->loadTextureDisabled(aBValue.getString());
						}
						break;
					}
				}

				break;
			}
			case BValue::Type::INTEGER:
			{
				switch (paramType)
				{
					case Params::LAYER:
					{
						aNode->setLocalZOrder(aBValue.getInt());
						break;
					}
					case Params::OPACITY:
					{
						aNode->setOpacity(aBValue.getInt());
						break;
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
					parentSize = Director::getInstance()->getWinSize();
				}

				switch (paramType)
				{
					case Params::POS_X:
					{
						aNode->setPositionX(parentSize.width * aBValue.getFloat());// +origin.x);
						break;
					}
					case Params::POS_Y:
					{
						aNode->setPositionY(parentSize.height * aBValue.getFloat());// +origin.y);
						break;
					}
					case Params::ANCH_X:
					{
						auto anch = aNode->getAnchorPoint();
						anch.x = aBValue.getFloat();
						aNode->setAnchorPoint(anch);
						break;
					}
					case Params::ANCH_Y:
					{
						auto anch = aNode->getAnchorPoint();
						anch.y = aBValue.getFloat();
						aNode->setAnchorPoint(anch);
						break;
					}
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

FiniteTimeAction* ViewManager::createActionFromBValue(const BValue& aBValue, Node* aNode)
{
	FiniteTimeAction* result = nullptr;

	auto getParamString = [](const BValueMap& aMap, const std::string& aParam)
	{
		std::string result;
		auto it = aMap.find(aParam);
		if (it != aMap.end() && it->second.isString())
		{
			result = it->second.getString();
		}
		return result;
	}; 
	auto getParamFloat = [](const BValueMap& aMap, const std::string& aParam)
	{
		float result = 0.f;
		auto it = aMap.find(aParam);
		if (it != aMap.end() 
			&& it->second.isFloat() || it->second.isDouble())
		{
			result = it->second.getFloat();
		}
		return result;

	};

	if (aBValue.isMap())
	{
		std::string actionVecName;
		std::string actionName;

		const auto& valMap = aBValue.getValueMap();
		for (auto it = valMap.begin(); it != valMap.end(); ++it)
		{
			if (it->second.isVector())
			{
				actionVecName = it->first;

				const auto& actionsVec = it->second.getValueVector();

				for (auto action : actionsVec)
				{
					if (action.isMap())
					{
						const auto& actionMap = action.getValueMap();

						auto it = actionMap.find("runAction");
						if (it != actionMap.end() && it->second.isString())
						{
							actionName = it->second.getString();
							if (actionName == "fade_in")
							{
								result = FadeIn::create( getParamFloat(actionMap, "duration") );
							}
							else if (actionName == "fade_out")
							{
								result = FadeOut::create( getParamFloat(actionMap, "duration") );
							}
							else if (actionName == "delay_time")
							{
								result = DelayTime::create( getParamFloat(actionMap, "duration") );
							}
							else if (actionName == "change_view")
							{
								std::string viewID = getParamString(actionMap, "id");
								result = CallFunc::create([this, viewID]() {
									changeView(viewID);
								});
							}
						}

						mViewsActions[aNode][actionVecName].pushBack(result);
					}
				}
			}
		}
	}

	return result;
}

void ViewManager::changeView(const std::string& aViewID)
{
	auto currentScene = SM->getCurrentScene();

	if (currentScene)
	{
		currentScene->removeAllChildren();

		auto view = getViewByID(aViewID);

		if (view)
		{
			currentScene->addChild(view);
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

void ViewManager::runActionForNode(Node* aNode, const std::string& aID)
{
	auto actionsListIt = mViewsActions.find(aNode);
	if (actionsListIt != mViewsActions.end())
	{
		auto& actionsList = actionsListIt->second;
		auto actionIt = actionsList.find(aID);
		if (actionIt != actionsList.end())
		{
			auto sequence = Sequence::create(actionIt->second);

			aNode->runAction(sequence);
		}
	}
}