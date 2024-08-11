#ifndef __VIEW_MANAGER_H__
#define __VIEW_MANAGER_H__

#include "CommonDefines.h"
#include "cocos2d.h"

_CSTART

class ViewManager
{
private:

	ViewManager();

	std::map<std::string, Node*> mViews;

public:

	static ViewManager* getInstance();

};

#define VM ViewManager::getInstance()

_CEND

#endif // __VIEW_MANAGER_H__
