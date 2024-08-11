#include "ViewManager.h"

_USEC

ViewManager::ViewManager()
{

}

ViewManager* ViewManager::getInstance()
{
	static ViewManager instance;
	return &instance;
}