#ifndef __VIEW_MANAGER_H__
#define __VIEW_MANAGER_H__

#include "CommonDefines.h"
#include "cocos2d.h"
#include "Basics/BValue.h"

_CSTART

class ViewManager
{
private:

	ViewManager();

	std::map<std::string, Node*> mViews;

	Node* createNodeFromBValue(const BValue& aBValue, Node* aParentNode = nullptr);
	void fillNodeParamFromBValue(Node* aNode, const std::string& aParamID, const BValue& aBValue);

public:

	static ViewManager* getInstance();

	Node* createViewByID(const std::string& aID);

	void removeViewByID(const std::string& aID);

	Node* getViewByID(const std::string& aID);

};

#define VM ViewManager::getInstance()

_CEND

#endif // __VIEW_MANAGER_H__
