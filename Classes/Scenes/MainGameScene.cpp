#include "MainGameScene.h"

#include "Managers/ViewManager.h"

_USEC

void MainGameScene::useDefaultView()
{
	auto view = VM->getViewByID("title");

	if (view)
	{
		this->addChild(view);
	}
}
