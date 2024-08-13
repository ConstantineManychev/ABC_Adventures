#include "GameDirector.h"

#include "ScenesManager.h"

#include "Scenes/MainGameScene.h"
#include "DataManager.h"
#include "ViewManager.h"

_USEC

GameDirector::GameDirector()
{

}

GameDirector* GameDirector::getInstance()
{
	static GameDirector instance;
	return &instance;
}

void GameDirector::startGame()
{
	DM->parseViewConfigs();

	SM->registerScene( "main", MainGameScene::create());

	SM->openScene("main");
}