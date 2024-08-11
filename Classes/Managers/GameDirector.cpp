#include "GameDirector.h"

#include "ScenesManager.h"

#include "Scenes/MainGameScene.h"

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
	SM->registerScene( "main", MainGameScene::create() );

	SM->openScene("main");
}